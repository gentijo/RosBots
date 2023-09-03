from microros import readROSMsg, publishMsg, registerEventSubscription, init_event_queue
import machine
import utime
import _thread
import gc



print("\r\nInit Event Queue")
init_event_queue()


def ros_event_thread():
    
    def ros_event_callback(data):
        print("Ros did something")
        #print(data)
    
    print("\r\nRegistgering Event Subscription")
    registerEventSubscription("CmdVel", "Twist", ros_event_callback)
    
    while True:
        print("In event Thread")
        utime.sleep(2)
        readROSMsg()
        
# Function that initializ
_thread.start_new_thread(ros_event_thread, ())

while True:
    print("In Main Thread")
    utime.sleep(2)
    
    