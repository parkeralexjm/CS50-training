import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    if "user_id" in session:
        username = session["user_id"]
        print(f"{username}")
    else:
        return apology("you are not logged in", 400)

    # fetch the database for index
    index = db.execute("SELECT * FROM display WHERE id=?", username)

    # fetch prices for each symbol and write into the display table
    counter = 0
    for row in index:
        price = lookup(index[counter]["symbol"])
        db.execute("UPDATE display SET price = ? WHERE symbol =?", price["price"], price["symbol"])
        db.execute("UPDATE display SET total = ? WHERE symbol =?", (price["price"] * index[counter]["shares"]), price["symbol"])
        db.execute("DELETE FROM display WHERE shares=?", 0)
        counter += 1

    temp_cash = db.execute("SELECT cash FROM users WHERE id=?", username)
    cash = temp_cash[0]["cash"]
    total_portfolio = db.execute("SELECT SUM(total) FROM display WHERE id=?", username)
    if total_portfolio[0]["SUM(total)"] != None:
        total = cash + total_portfolio[0]["SUM(total)"]
    else:
        total = cash

    # update index with new information
    index = db.execute("SELECT * FROM display WHERE id=?", username)
    return render_template("index.html", index=index, cash=cash, total=total)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # get stock name
        lower_symbol = request.form.get("symbol")
        symbol = lower_symbol.upper()
        # get amount of stocks to buy
        amount = request.form.get("shares")
        if not amount.isdigit():
            return apology("You cannot purchase partial shares.")

        # print("amount = ", int(amount))
        # if amount < 1:
        #     return apology("You must purchase 1 or more stocks", 400)
        # if amount :
        #     return apology("You must enter a whole number", 400)

        # get id from the user
        if "user_id" in session:
            username = session["user_id"]
        else:
            return apology("you are not logged in", 400)

        # lookup the stock price
        if symbol == None:
            return apology("Enter a stock symbol", 400)
        stock_info = lookup(symbol)

        if stock_info == None:
            return apology("Stock does not exist", 400)

        # find the amount of cash the user has
        cash_db = db.execute("SELECT * FROM users WHERE id=?", username)
        cash = cash_db[0]["cash"]

        # get date and time
        now = datetime.now()
        dt_string = now.strftime("%d/%m/%Y %H:%M:%S")

        # track the purchase on finance db
        price = stock_info["price"]
        name = stock_info["name"]
        db.execute("INSERT INTO transactions (id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, ?)", username, symbol, amount, price, dt_string)
        if cash < (float(amount) * price):
            # return error apology
            return apology("You cannot afford that many shares", 400)
        else:
            cash = (cash - (float(amount) * price))

        # update cash amount for user
        db.execute("UPDATE users SET cash = ? WHERE id=?", cash, username)

        # update display table for user
        shares_exist = db.execute("SELECT symbol FROM display WHERE id = ? AND symbol = ?", username, symbol)
        if len(shares_exist) != 1:
            db.execute("INSERT INTO display (id, symbol, name, shares) VALUES(?, ?, ?, ?)",username, symbol, name, amount)
        else:
            db.execute("UPDATE display SET shares = shares+? WHERE id=? AND symbol=?",amount, username, symbol)

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""

    # get id from the user
    if "user_id" in session:
        username = session["user_id"]
    else:
        return apology("you are not logged in", 400)

    transactions = db.execute("SELECT * FROM transactions WHERE id=?", username)

    return render_template("history.html", transactions=transactions)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Get input from the user
        symbol = request.form.get("symbol")
        if symbol == None:
            return apology("Enter a stock symbol", 400)
        # get a dictionary of the quote by using the lookup function
        quotes = lookup(symbol)

        if quotes == None:
            return apology("Stock does not exist", 400)

        return render_template("quoted.html", quotes=quotes)

    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # Set variables
    username = request.form.get("username")

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username does not already exist in db
        duplicate = db.execute("SELECT COUNT(id) FROM users WHERE username = ?", username)
        if duplicate[0]["COUNT(id)"] != 0:
            return apology("username is already taken", 400)

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password") or not request.form.get("confirmation"):
            return apology("must provide password", 400)

        # Ensure both passwords are the same
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("passwords must match", 400)

    # Insert data into users storing a hash for the password and a username
        password = generate_password_hash(request.form.get("password"), method='pbkdf2:sha256', salt_length=8)
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", username, password)

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

    # return apology("TODO")
    return redirect("/")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # get stock name
        lower_symbol = request.form.get("symbol")
        symbol = lower_symbol.upper()
        print(symbol)

        # get amount of stocks to sell and change to a negative number
        amount = request.form.get("shares")
        if int(amount) < 1 or amount == None:
            return apology("You must sell 1 or more stocks", 400)
        print(amount)

        # get id from the user
        if "user_id" in session:
            username = session["user_id"]
        else:
            return apology("you are not logged in", 400)

        user_stocks = db.execute("SELECT symbol FROM display WHERE id=? AND symbol=?", username, symbol)
        print(user_stocks)
        if user_stocks == None:
            return apology("You must own this stock", 400)

        # lookup the stock price
        # if symbol == "":
        #     return apology("Enter a stock symbol", 400)
        stock_info = lookup(symbol)
        # if stock_info == None:
        #     return apology("Stock does not exist", 400)

        # find the amount of cash the user has
        cash_db = db.execute("SELECT * FROM users WHERE id=?", username)
        cash = cash_db[0]["cash"]

        # get date and time
        now = datetime.now()
        dt_string = now.strftime("%d/%m/%Y %H:%M:%S")

        # track the sale on finance db
        price = stock_info["price"]
        shares = int(amount) * -1

        # check if there are enough shares to sell
        current_shares = db.execute("SELECT shares FROM display WHERE symbol = ?", symbol)
        if current_shares[0]["shares"] < int(amount) or current_shares == None:
            # return error apology
            return apology("You do not have enough shares to sell", 400)
        else:
            db.execute("UPDATE display SET shares = shares-?", int(amount))
            db.execute("INSERT INTO transactions (id, symbol, shares, price, transacted) VALUES (?, ?, ?, ?, ?)", username, symbol, shares, price, dt_string)

        return redirect("/")

    else:
        username = session["user_id"]
        SYMBOLS = db.execute("SELECT symbol FROM display WHERE id=?", username)
        return render_template("sell.html", symbol=SYMBOLS)


@app.route("/add_cash", methods=["GET", "POST"])
@login_required
def add_cash():
    """Add cash to account"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        # get id from the user
        if "user_id" in session:
            username = session["user_id"]
        else:
            return apology("you are not logged in", 400)

        add = request.form.get("add")
        # update cash amount for user
        db.execute("UPDATE users SET cash = cash+? WHERE id=?", add, username)

        return redirect("/buy")

    else:
        return render_template("index.html")