from flask import Flask, request, render_template
app = Flask(__name__)


@app.route('/')
def hello_world():
    with open('data.txt', 'r') as f:
        s = f.read().split(',')
    return render_template('test.html', temper=s[0], humidity=s[1])


if __name__ == '__main__':
    app.run(port=5002, debug=True, host='0.0.0.0')
    info = 38
