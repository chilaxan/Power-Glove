import requests, macmouse

url = 'https://powerglove.chilaxan.tech'
password = input('password? ')

while True:
    data = requests.get(url + '/?p=' + password).json()
    gestures = data['gestures']
    Y, X = data['gyros']
    for gest in gestures:
        match gest:
            case 'Pinch':
                macmouse.click()
            case 'Double Pinch':
                macmouse.double_click()
            case 'Clench':
                macmouse.wheel(-20)
            case 'Double Clench':
                macmouse.wheel(20)
    cX, cY = macmouse.get_position()
    if (X < -0.4):
        cX += 10
    elif (X > 0.4):
        cX -= 10
    if (Y > 0.4):
        cY += 10
    elif (Y < -0.4):
        cY -= 10
    macmouse.move(cX, cY)
