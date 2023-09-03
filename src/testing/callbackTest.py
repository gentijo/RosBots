from microros import publishMsg,registerEventSubscription
from microros import init_ros_mp_event_system

init_ros_mp_event_system()

def ros_event_callback(data):
    print("Ros did something")
    print(data)
             
print("\r\nRegistgering Event Subscription")
registerEventSubscription("CmdVel", "Twist", ros_event_callback) 


