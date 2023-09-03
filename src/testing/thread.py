import machine
import utime
import _thread
import gc
from microros import readROSMsg, publishMsg

gc.enable()

print(gc.mem_free())

gc.collect()
gc.disable()

# We configure the pin of the internal led as an output and
# we assign to internal_led

# We create a semaphore (A.K.A lock)
baton = _thread.allocate_lock()


# Function that will block the thread with a while loop
# which will simply display a message every second

def second_thread():
    
    print("In 2nd thread - ROS Message")

    while True:
        readROSMsg()

    print("Exit 2nd thread")

        # We release the traffic light lock
def third_thread():
    while True:
        # We acquire the traffic light lock
        
        baton.acquire()
        print("Hello, I'm here in the third thread writting every three seconds")
        baton.release()
        
        utime.sleep(3)
        
# Function that initializes execution in the second core
# The second argument is a list or dictionary with the arguments
# that will be passed to the function.
_thread.start_new_thread(second_thread, ())
_thread.start_new_thread(third_thread, ())

# Second loop that will block the main thread, and what it will do
# that the internal led blinks every half second
while True:
    # We acquire the semaphore lock
    
    baton.acquire()
    print("In Main Thread")
    baton.release()
    
    utime.sleep(0.5)
