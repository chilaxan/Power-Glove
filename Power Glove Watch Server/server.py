from flask import Flask, request, jsonify

app = Flask(__name__)

dev_data = {
    'gyros': [],
    'gestures': []
}

password = 'REDACTED'

@app.route('/gyros', methods=['GET'])
def getgyro():
    if not request.args.get('p') == password:
        return '[]'
    gyros = dev_data['gyros']
    dev_data['gyros'] = []
    return jsonify(gyros)

@app.route('/gestures', methods=['GET'])
def getgestures():
    if not request.args.get('p') == password:
        return '[]'
    gests = dev_data['gestures']
    dev_data['gestures'] = []
    return jsonify(gests)

@app.route('/gyro', methods=['POST'])
def setgyro():
    if not request.json.get('p') == password or not request.json.get('g'):
        return ''
    dev_data['gyros'].append(request.json['g'])
    return ''

@app.route('/gesture', methods=['POST'])
def addgesture():
    if not request.json.get('p') == password or not request.json.get('g'):
        return ''
    dev_data['gestures'].append(request.json['g'])
    return ''

if __name__ == '__main__':
    app.run(port=1337)
