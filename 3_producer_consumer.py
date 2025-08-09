import threading
import time
import random

# Constants
BUFFER_SIZE = 5

# Shared resources
buffer = []
mutex = threading.Lock()
empty_slots = threading.Semaphore(BUFFER_SIZE)
filled_slots = threading.Semaphore(0)

def producer():
    """
    Produces items and puts them into the buffer.
    """
    global buffer
    while True:
        item = random.randint(1, 100) # Generate a random item
        
        # 1. Wait if there are no empty slots
        empty_slots.acquire()
        
        # 2. Acquire lock for the critical section
        mutex.acquire()
        
        # --- Critical Section ---
        try:
            buffer.append(item)
            print(f"Producer produced {item}. Buffer: {buffer}")
        finally:
            # 3. Release lock after accessing the buffer
            mutex.release()
            
        # 4. Signal that there is one more filled slot
        filled_slots.release()
        
        # Simulate time taken to produce the item
        time.sleep(random.uniform(0.5, 1.5))

def consumer():
    """
    Consumes items from the buffer.
    """
    global buffer
    while True:
        # 1. Wait if there are no items to consume
        filled_slots.acquire()
        
        # 2. Acquire lock for the critical section
        mutex.acquire()
        
        # --- Critical Section ---
        try:
            item = buffer.pop(0) # Consume the first item in the queue
            print(f"Consumer consumed {item}. Buffer: {buffer}")
        finally:
            # 3. Release lock after accessing the buffer
            mutex.release()
        
        # 4. Signal that there is one more empty slot
        empty_slots.release()
        
        # Simulate time taken to consume the item
        time.sleep(random.uniform(1, 2))


if __name__ == "__main__":
    print("Starting Producer-Consumer simulation...")
    
    # Create producer and consumer threads
    producer_thread = threading.Thread(target=producer)
    consumer_thread = threading.Thread(target=consumer)
    
    # Start the threads
    producer_thread.start()
    consumer_thread.start()
    
    # Wait for the threads to complete (they won't in this infinite loop)
    producer_thread.join()
    consumer_thread.join()