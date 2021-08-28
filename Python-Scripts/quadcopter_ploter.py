import dash, datetime, csv, plotly, threading, socket, re
import plotly.subplots
import numpy
import dash_core_components as dcc
import dash_html_components as html
import plotly.graph_objects as go
from dash.dependencies import Input, Output
import os, queue

data_file = 'quadcopter_raw.csv'
mapbox_access_token = 'pk.eyJ1IjoiZmp1bGlvZm9udGVzIiwiYSI6ImNrbHlhem1yZjNodmcycW4xM2Ntb2JrYzAifQ.lFyfVOYUxrRhl1U1i8jg0A'

PID_TYPES = ["alt_p","r_and_p_p","yaw_p",
            "alt_i","r_and_p_i","yaw_i",
            "alt_d","r_and_p_d","yaw_d"
            ]

run = True
last_data_transmitted = ''
q = queue.Queue()

def communicate_with_quad(ip,port):
    global last_data_transmitted
    
    s = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
    print("trying to connect to ",ip,port)
    s.bind((ip, port))
    s.listen(1)
    # couple of vars
    conn, addr = s.accept()
    quad_pitch,quad_roll,quad_yaw,quad_altitude = [],[],[],[]
    quad_temperature,heading,lat,lon = [],[],[],[]
    u_roll,u_pitch,u_yaw,u_altitude = [],[],[],[]
    cmd_roll,cmd_pitch,cmd_yaw,cmd_altitude = [],[],[],[]
    
    while run:
        # send vars
        if not q.empty():
            while not q.empty():
                last_data_transmitted = q.get()
            # send only the last value
            conn.sendall(last_data_transmitted.encode('utf-8'))
            print("Sent:",last_data_transmitted.encode('utf-8'))

        # wait new reading
        data = conn.recv(1024)
        try:
            received_data_decoded = data.decode("utf-8")
        except:
            continue

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

            if(lat != [] and lon != []): print(lat,lon)
            else :
                # force lat and lon
                lat,lon = [],[]
                lat.append(41.026)
                lon.append(-8.453111)

            # save to csv file
            data = []
            data.append(str(int(datetime.datetime.now().timestamp())))
            with open(data_file, 'a+', newline='', encoding='utf-8') as csv_file:
                quad_writer = csv.writer(csv_file, delimiter=',', quotechar='"', quoting=csv.QUOTE_MINIMAL)
                data = data + quad_roll + quad_pitch + quad_yaw + quad_altitude + quad_temperature + u_roll + u_pitch + u_yaw + u_altitude + cmd_roll + cmd_pitch + cmd_yaw + cmd_altitude + heading + lat + lon
                quad_writer.writerow(data)
            
            # reset variables
            quad_pitch,quad_roll,quad_yaw,quad_altitude = [],[],[],[]
            quad_temperature,heading,lat,lon = [],[],[],[]
            u_roll,u_pitch,u_yaw,u_altitude = [],[],[],[]
            cmd_roll,cmd_pitch,cmd_yaw,cmd_altitude = [],[],[],[]

def get_data(timestamp):
    # more or less 3 seconds
    upLimit = timestamp + datetime.timedelta(seconds=3)
    downLimit = timestamp - datetime.timedelta(seconds=3)

    with open(data_file, mode='r') as csv_file:
        csv_reader = csv.DictReader(csv_file)
        lastRow = []
        for row in csv_reader:
            # search desired timestamp
            read_timestamp = datetime.datetime.fromtimestamp(int(row["timestamp"]))
            if( (read_timestamp <= upLimit) and (read_timestamp >= downLimit) ):
                return row
            # save last row
            lastRow = row

    return lastRow

def get_data_from_interval(start_timestamp,stop_timestamp):
    # more or less 3 seconds
    upLimit = stop_timestamp + datetime.timedelta(seconds=3)
    downLimit = start_timestamp - datetime.timedelta(seconds=3)

    with open(data_file, mode='r') as csv_file:
        csv_reader = csv.DictReader(csv_file)
        rows = []
        for row in csv_reader:
            # search desired timestamp
            read_timestamp = datetime.datetime.fromtimestamp(int(row["timestamp"]))
            if( (read_timestamp <= upLimit) and (read_timestamp >= downLimit) ):
                rows.append(row)

    return rows
            

external_stylesheets = ['https://codepen.io/chriddyp/pen/bWLwgP.css']

app = dash.Dash(__name__, external_stylesheets=external_stylesheets)
app.layout = html.Div([
    html.Div([
        html.H4('Quadcopter (Input Interface)'),
        html.Table([
            html.Tr([
                html.Th("Altitude",colSpan=3),
                html.Th("Pitch & Roll",colSpan=3),
                html.Th("Yaw",colSpan=3)
            ]),
            html.Tr([
                html.Td("P"),
                html.Td(
                    dcc.Input(
                        id="input_alt_p",
                        type="range",
                        placeholder="input type range",
                        min=0,
                        max=20,
                        step=0.5,
                        value='0'
                    )
                ),
                html.Td("10",id='output_alt_p'),
                html.Td("P"),
                html.Td(
                    dcc.Input(
                        id="input_r_and_p_p",
                        type="range",
                        placeholder="input type range",
                        min=0,
                        max=20,
                        step=0.5,
                        value='0'
                    )
                ),
                html.Td("10",id='output_r_and_p_p'),
                html.Td("P"),
                html.Td(
                    dcc.Input(
                        id="input_yaw_p",
                        type="range",
                        placeholder="input type range",
                        min=0,
                        max=20,
                        step=0.5,
                        value='0'
                    )
                ),
                html.Td("10",id='output_yaw_p')
            ]),
            html.Tr([
                html.Td("I"),
                html.Td(
                    dcc.Input(
                        id="input_alt_i",
                        type="range",
                        placeholder="input type range",
                        min=0,
                        max=20,
                        step=0.5,
                        value='0'
                    )
                ),
                html.Td("10",id="output_alt_i"),
                html.Td("I"),
                html.Td(
                    dcc.Input(
                        id="input_r_and_p_i",
                        type="range",
                        placeholder="input type range",
                        min=0,
                        max=20,
                        step=0.5,
                        value='0'
                    )
                ),
                html.Td("10",id="output_r_and_p_i"),
                html.Td("I"),
                html.Td(
                    dcc.Input(
                        id="input_yaw_i",
                        type="range",
                        placeholder="input type range",
                        min=0,
                        max=20,
                        step=0.5,
                        value='0'
                    )
                ),
                html.Td("10",id="output_yaw_i")
            ]),
            html.Tr([
                html.Td("D"),
                html.Td(
                    dcc.Input(
                        id="input_alt_d",
                        type="range",
                        placeholder="input type range",
                        min=0,
                        max=20,
                        step=0.5,
                        value='0'
                    )
                ),
                html.Td("10",id="output_alt_d"),
                html.Td("D"),
                html.Td(
                    dcc.Input(
                        id="input_r_and_p_d",
                        type="range",
                        placeholder="input type range",
                        min=0,
                        max=20,
                        step=0.5,
                        value='0'
                    )
                ),
                html.Td("10",id="output_r_and_p_d"),
                html.Td("D"),
                html.Td(
                    dcc.Input(
                        id="input_yaw_d",
                        type="range",
                        placeholder="input type range",
                        min=0,
                        max=20,
                        step=0.5,
                        value='0'
                    )
                ),
                html.Td("10",id="output_yaw_d")
            ]),
        ], style = {'width':'100%'})
    ]),

    html.Div([
        html.H4('Quadcopter (Graphical Interface)'),
        dcc.Graph(id='gauge-indicators'),
        dcc.Graph(id='live-update-graph'),
        dcc.Interval(
            id='interval-component',
            interval = 500, # in milliseconds
            n_intervals = 0
        )
    ])
])

# # Update Interval as soon we have n samples
# @app.callback(Output('interval-component', 'interval'),
#               Input('interval-component','n_intervals'))
# def update_interval(n):
#     return 500

@app.callback(
    [Output("output_{}".format(_), "children") for _ in PID_TYPES],
    [Input("input_{}".format(_), "value") for _ in PID_TYPES],
)
def cb_render(*vals):
    global last_data_transmitted
    data_format = 'AA{:05.2f},{:05.2f},{:05.2f}BB{:05.2f},{:05.2f},{:05.2f}CC{:05.2f},{:05.2f},{:05.2f}DD\r'
    data = data_format.format(float(vals[0]),float(vals[3]),float(vals[6]),float(vals[1]),float(vals[4]),float(vals[7]),float(vals[2]),float(vals[5]),float(vals[8]))
    res = ()
    for val in vals:
        if val:
            res += ("{:.2f}".format(float(val)),)
    if last_data_transmitted != data:
        q.put(data)
    return res
    

# Multiple components can update everytime interval gets fired.
@app.callback(Output('live-update-graph', 'figure'),
              Input('interval-component', 'n_intervals'))
def update_graph_live(n):
    data = {
        'time'             : [],
        'quad_roll'        : [],
        'quad_pitch'       : [],
        'quad_yaw'         : [],
        'quad_altitude'    : [],
        'quad_temperature' : [],
        'u_roll'           : [],
        'u_pitch'          : [],
        'u_yaw'            : [],
        'u_altitude'       : [],
        'cmd_roll'         : [],
        'cmd_pitch'        : [],
        'cmd_yaw'          : [],
        'cmd_altitude'     : [],
        'heading'          : [],
        'lat'              : [],
        'lon'              : []
    }

    # Collect some data [from last hour until now]
    # timestamp,quad_roll,quad_pitch,quad_yaw,quad_altitude,quad_temperature,u_roll,u_pitch,u_yaw,u_altitude,cmd_roll,cmd_pitch,cmd_yaw,cmd_altitude,heading,lat,lon
    # 1615072045,25.2,25.5,180.23,300,24.4,-25,-25,0,300,0,0,0,0,180,41.026,-8.453111
    rows = get_data_from_interval(datetime.datetime.now()-datetime.timedelta(seconds=60),datetime.datetime.now())
    #rows = get_data_from_interval(datetime.datetime.fromtimestamp(1611599124),datetime.datetime.fromtimestamp(1611600255))

    for row in rows:
        data['time'].append(datetime.datetime.fromtimestamp(int(row["timestamp"])))
        data['quad_roll'].append(float(row["quad_roll"]))
        data['quad_yaw'].append(float(row["quad_yaw"]))
        data['quad_pitch'].append(float(row["quad_pitch"]))
        data['quad_altitude'].append(float(row["quad_altitude"]))
        data['quad_temperature'].append(float(row["quad_temperature"]))
        data['u_roll'].append(float(row["u_roll"]))
        data['u_pitch'].append(float(row["u_pitch"]))
        data['u_yaw'].append(float(row["u_yaw"]))
        data['u_altitude'].append(float(row["u_altitude"]))
        data['cmd_roll'].append(float(row["cmd_roll"]))
        data['cmd_pitch'].append(float(row["cmd_pitch"]))
        data['cmd_yaw'].append(float(row["cmd_yaw"]))
        data['cmd_altitude'].append(float(row["cmd_altitude"]))
        data['heading'].append(float(row["heading"]))
        data['lat'].append(float(row["lat"]))
        data['lon'].append(float(row["lon"]))

    # Create the graph with subplots
    fig =  plotly.subplots.make_subplots(
        subplot_titles=(
            "Altitude", 
            "Pitch",
            "Roll", 
            "Yaw"
        ),
        rows=4, 
        cols=1,
        vertical_spacing=0.05)
    
    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['quad_altitude'], 
            name='Altitude',
            line=dict(color='royalblue', width=2, dash='dot')
        ),
        row=1, 
        col=1
    )
    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['u_altitude'], 
            name='u(t)-altitude',
            line=dict(color='firebrick', width=2, dash='dash')
        ),
        row=1, 
        col=1
    )
    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['cmd_altitude'], 
            name='r(t)-altitude',
            line=dict(color='green', width=2)
        ),
        row=1, 
        col=1
    )
    
    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['quad_pitch'], 
            name='Pitch',
            line=dict(color='royalblue', width=2, dash='dot')
        ),
        row=2, 
        col=1
    )
    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['u_pitch'], 
            name='u(t)-pitch',
            line=dict(color='firebrick', width=2, dash='dash')
        ),
        row=2, 
        col=1
    )
    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['cmd_pitch'], 
            name='r(t)-pitch',
            line=dict(color='green', width=2)
        ),
        row=2, 
        col=1
    )

    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['quad_roll'], 
            name='Roll',
            line=dict(color='royalblue', width=2, dash='dot')
        ),
        row=3, 
        col=1
    )
    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['u_roll'], 
            name='u(t)-roll',
            line=dict(color='firebrick', width=2, dash='dash')
        ),
        row=3, 
        col=1
    )
    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['cmd_roll'], 
            name='r(t)-roll',
            line=dict(color='green', width=2)
        ),
        row=3, 
        col=1
    )

    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['quad_yaw'], 
            name='Yaw',
            line=dict(color='royalblue', width=2, dash='dot')
        ),
        row=4, 
        col=1
    )
    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['u_yaw'], 
            name='u(t)-yaw',
            line=dict(color='firebrick', width=2, dash='dash')
        ),
        row=4, 
        col=1
    )
    fig.append_trace(
        go.Scatter(
            x=data['time'], 
            y=data['cmd_yaw'], 
            name='r(t)-yaw',
            line=dict(color='green', width=2)
        ),
        row=4, 
        col=1
    )

    # Update xaxis properties
    fig.update_xaxes(title_text="Time (HH:MM:SS)", row=1, col=1)
    fig.update_xaxes(title_text="Time (HH:MM:SS)", row=2, col=1)
    fig.update_xaxes(title_text="Time (HH:MM:SS)", row=3, col=1)
    fig.update_xaxes(title_text="Time (HH:MM:SS)", row=4, col=1)

    # Update yaxis properties
    fig.update_yaxes(title_text="cm", row=1, col=1)
    fig.update_yaxes(title_text="degree", row=2, col=1)
    fig.update_yaxes(title_text="degree", row=3, col=1)
    fig.update_yaxes(title_text="degree", row=4, col=1)

    fig.update_layout(
        height=2000, 
        width=None, 
        title_text="Graphical Visualization",
        showlegend=True
    )

    return fig

# Multiple components can update everytime interval gets fired.
@app.callback(Output('gauge-indicators', 'figure'),
              Input('interval-component', 'n_intervals'))
def update_graph_live(n):
    current = get_data(datetime.datetime.now())
    last = get_data(datetime.datetime.now()-datetime.timedelta(seconds=30))

    fig = go.Figure()

    fig.add_trace(
        go.Barpolar(
            r=[5],
            theta=[float(current['heading'])],
            width=[10,],
            marker_color=["#E4FF87"],
            marker_line_color="black",
            marker_line_width=2,
            opacity=0.8
        )
    )

    fig.add_trace(
        go.Indicator(
            domain = {'row': 0, 'column': 0},
            value = float(current["quad_temperature"]),
            mode = "gauge+number+delta",
            # title = {'text': "Temperature",'font': {'size': 24}},
            delta = {
                'reference': float(last["quad_temperature"]),
                'increasing': {'color': "green"},
                'decreasing': {'color': "red"}
            },
            gauge = {
                'axis': {
                    'range': [0, 30],
                    'tickwidth': 1, 
                    'tickcolor': "darkblue"
                },
                'borderwidth': 2,
                'bordercolor': "gray",
                'bar': {'color': "green"},
                'steps' : [
                    {'range': [0, 10], 'color': "#ff0000"},
                    {'range': [10.1, 15], 'color': "#ffff02"},
                    {'range': [15.1, 25], 'color': "#00e400"},
                    {'range': [25.1, 30], 'color': "#ff7e00"}
                ]
            }
        )
    )

    fig.add_trace(
        go.Scattermapbox(
            lat=[float(current['lat'])],
            lon=[float(current['lon'])],
            mode='markers',
            marker=go.scattermapbox.Marker(
                size=14
            ),
            text=['Montreal']
        )
    )


    fig.update_layout(
        grid = {'rows': 1, 'columns': 3, 'pattern': "independent"},
        polar = dict(
            radialaxis = dict(range=[0, 5], showticklabels=False, ticks=''),
            angularaxis = dict(showticklabels=True, ticks=''),
            domain = {'row': 0, 'column': 1}
        ),
        hovermode='closest',
        mapbox = dict(
            accesstoken=mapbox_access_token,
            bearing=0,
            center=go.layout.mapbox.Center(
                lat=round(float(current['lat'])*100)/100,
                lon=round(float(current['lon'])*100)/100
            ),
            pitch=0,
            zoom=12,
            domain = {'row': 1, 'column': 2}
        )
    )

    return fig

if __name__ == '__main__':
    print('starting thread')
    x = threading.Thread(target=communicate_with_quad, args=('0.0.0.0', 9090,))
    x.setDaemon(True)
    x.start()

    print('running app')
    app.run_server(host='0.0.0.0', port=4444)

