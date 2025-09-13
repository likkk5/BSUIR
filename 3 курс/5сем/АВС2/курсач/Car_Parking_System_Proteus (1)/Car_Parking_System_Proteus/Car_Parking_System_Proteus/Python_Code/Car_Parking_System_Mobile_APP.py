import Adafruit_DHT
import os,sys
import paho.mqtt.client as paho
import urlparse
import time
 
def on_connect(self, mosq, obj, rc):
        self.subscribe("Fan", 0)
    
def on_message(mosq, obj, msg):
    print(msg.topic + " " + str(msg.qos) + " " + str(msg.payload))
    # Give 5 second delay

def on_publish(mosq, obj, mid):
    print("mid: " + str(mid))

    
def on_subscribe(mosq, obj, mid, granted_qos):
    print("Subscribed: " + str(mid) + " " + str(granted_qos))
    

mqttc = paho.Client()                        # object declaration
# Assign event callbacks
mqttc.on_message = on_message                          # called as callback
mqttc.on_connect = on_connect
mqttc.on_publish = on_publish
mqttc.on_subscribe = on_subscribe

url_str = os.environ.get('CLOUDMQTT_URL', 'tcp://broker.emqx.io:1883') 
url = urlparse.urlparse(url_str)
mqttc.connect(url.hostname, url.port)
 
rc = 0
while rc == 0: 
    rc = mqttc.loop()
      mqttc.publish("humidity",str(humidity))
      time.sleep(1)


