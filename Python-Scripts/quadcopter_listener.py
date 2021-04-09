import socket, re, datetime, csv

s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
s.bind(('192.168.100.1', 9090))
s.listen(1)
conn, addr = s.accept()

quad_pitch,quad_roll,quad_yaw,quad_altitude = [],[],[],[]
quad_temperature,heading,lat,lon = [],[],[],[]
u_roll,u_pitch,u_yaw,u_altitude = [],[],[],[]
cmd_roll,cmd_pitch,cmd_yaw,cmd_altitude = [],[],[],[]
while 1:
    data = conn.recv(1024)

    received_data_decoded = data.decode("utf-8")

    res = re.findall("Pitch : (-?\d+.\d+)", received_data_decoded)
    if (res): quad_pitch.append(res[0])
    res = re.findall("Roll : (-?\d+.\d+)", received_data_decoded)
    if (res): quad_roll.append(res[0])
    res = re.findall("Yaw : (-?\d+.\d+)", received_data_decoded)
    if (res): quad_yaw.append(res[0])
    res = re.findall("Alt : (-?\d+.\d+)", received_data_decoded)
    if (res): quad_altitude.append(res[0])
    res = re.findall("Temp : (-?\d+.\d+)", received_data_decoded)
    if (res): quad_temperature.append(res[0])

    res = re.findall("Roll_cmd : (-?\d+.\d+)", received_data_decoded)
    if (res): cmd_roll.append(res[0])
    res = re.findall("Pitch_cmd : (-?\d+.\d+)", received_data_decoded)
    if (res): cmd_pitch.append(res[0])
    res = re.findall("Yaw_cmd : (-?\d+.\d+)", received_data_decoded)
    if (res): cmd_yaw.append(res[0])
    res = re.findall("Thrust_cmd : (-?\d+.\d+)", received_data_decoded)
    if (res): cmd_altitude.append(res[0])

    res = re.findall("Thrust_u : (-?\d+.\d+)", received_data_decoded)
    if (res): u_altitude.append(res[0])
    res = re.findall("Pitch_u : (-?\d+.\d+)", received_data_decoded)
    if (res): u_pitch.append(res[0])
    res = re.findall("Yaw_u : (-?\d+.\d+)", received_data_decoded)
    if (res): u_yaw.append(res[0])
    res = re.findall("Roll_u : (-?\d+.\d+)", received_data_decoded)
    if (res): u_roll.append(res[0])

    res = re.findall("Heading : (-?\d+.\d+)", received_data_decoded)
    if (res): heading.append(res[0])
    res = re.findall("(\d+)\?(\d+)'(\d+)''(N|S)", received_data_decoded)
    if (res):
        res = res[0]
        if(res[3] == 'N'): lat.append(int(res[0]) + int(res[1])/60 + int(res[2])/3600)
        else: lat.append( -(int(res[0]) + int(res[1])/60 + int(res[2])/3600) )
    res = re.findall("(\d+)\?(\d+)'(\d+)''(E|W)", received_data_decoded)
    if (res):
        res = res[0]
        if(res[3] == 'E'): lon.append(int(res[0]) + int(res[1])/60 + int(res[2])/3600)
        else: lon.append( -(int(res[0]) + int(res[1])/60 + int(res[2])/3600) )

    if (quad_pitch != [] and quad_roll != [] and quad_yaw != [] and quad_altitude != [] and
       quad_temperature != [] and heading != [] and 
       u_roll != [] and u_pitch != [] and u_yaw != [] and u_altitude != [] and
       cmd_roll != [] and cmd_pitch != [] and cmd_yaw != [] and cmd_altitude != []):

        if(lat == [] or lon == []):
            # force lat and lon
            lat,lon = [],[]
            lat.append(41.026)
            lon.append(-8.453111)

        # save to csv file
        data = []
        data.append(str(int(datetime.datetime.now().timestamp())))
        with open('quadcopter_raw.csv', 'a+', newline='', encoding='utf-8') as csv_file:
            quad_writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
            data = data + quad_roll + quad_pitch + quad_yaw + quad_altitude + quad_temperature + u_roll + u_pitch + u_yaw + u_altitude + cmd_roll + cmd_pitch + cmd_yaw + cmd_altitude + heading + lat + lon
            quad_writer.writerow(data)
        
        # reset variables
        quad_pitch,quad_roll,quad_yaw,quad_altitude = [],[],[],[]
        quad_temperature,heading,lat,lon = [],[],[],[]
        u_roll,u_pitch,u_yaw,u_altitude = [],[],[],[]
        cmd_roll,cmd_pitch,cmd_yaw,cmd_altitude = [],[],[],[]

    if not data:
        break
    # conn.sendall(data)
conn.close()