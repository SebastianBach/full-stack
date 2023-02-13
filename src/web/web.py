import os
import platform
import subprocess
import sys

from flask import (Flask, escape, render_template, request, send_file,
                   send_from_directory)

resources_folder = sys.argv[1]
templates_folder = os.path.join(resources_folder, "templates")
app = Flask(__name__, template_folder=templates_folder)


executable = {}
executable["Windows"] = "cmdl.exe"
executable["Linux"] = "cmdl"

cmdl_path = os.path.join(sys.argv[2], executable[platform.system()])


@app.route('/')
def index():
    """Returns the front page."""
    return render_template('index.html')


@app.route('/style.css')
def style():
    """Returns the CSS file."""
    return send_from_directory(resources_folder, 'style.css', mimetype='text/css')


@app.route('/web-convert', methods=['POST'])
def search_image():
    """Performs the operation and returns the result."""

    data = request.form['data']

    res = subprocess.run([cmdl_path, data], capture_output=True, text=True)

    return render_template('result.html', data=data, result=res.stdout)

if __name__ == '__main__':
    app.run(host='0.0.0.0')
