from microros import readROSMsg, publishMsg, registerEventSubscription
from microros import init_event_queue, createObjFromThread, readObjFromThread
import machine
import utime
import _thread
import gc



print("\r\nInit Event Queue")
init_event_queue()

print("On MP Main thread create/read Queue")
createObjFromThread()
print(readObjFromThread())


def ros_event_thread():
    print ("read Obj from Event thread")
    print(readObjFromThread())
    
    print ("create/read Obj from Event thread")
    createObjFromThread()
    print(readObjFromThread())

    def ros_event_callback(data):
        print("Ros did something")
        print(readObjFromThread())
   
    print("\r\nRegistgering Event Subscription")
    registerEventSubscription("CmdVel", "Twist", ros_event_callback)
    
    while True:
        print("In event Thread")
        utime.sleep(2)
        readROSMsg()
        print(readObjFromThread())

        
# Function that initializ
_thread.start_new_thread(ros_event_thread, ())

while True:
    print("In Main Thread")
    utime.sleep(2)
    
    