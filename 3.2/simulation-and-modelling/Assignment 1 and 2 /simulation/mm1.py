import math
import random

# Global variables
Q_LIMIT = 100
BUSY = 1
IDLE = 0

# Simulation state - using dictionaries for better scope control
state = {
    'next_event_type': 0,
    'num_custs_delayed': 0,
    'num_delays_required': 0,
    'num_in_q': 0,
    'server_status': IDLE,
    'area_num_in_q': 0.0,
    'area_server_status': 0.0,
    'mean_interarrival': 0.0,
    'mean_service': 0.0,
    'sim_time': 0.0,
    'time_arrival': [0.0] * (Q_LIMIT + 1),
    'time_last_event': 0.0,
    'time_next_event': [0.0, 0.0, 0.0],  # Index 0 unused
    'total_of_delays': 0.0
}

def logrand(stream):
    return random.random()

def expon(mean):
    return -mean * math.log(logrand(1))

def initialize():
    state.update({
        'sim_time': 0.0,
        'server_status': IDLE,
        'num_in_q': 0,
        'time_last_event': 0.0,
        'num_custs_delayed': 0,
        'total_of_delays': 0.0,
        'area_num_in_q': 0.0,
        'area_server_status': 0.0,
        'time_next_event': [
            0.0,
            state['sim_time'] + expon(state['mean_interarrival']),
            1.0e30
        ]
    })

def timing():
    min_time = 1.0e29
    state['next_event_type'] = 0
    
    for i in range(1, 3):  # Only 2 event types
        if state['time_next_event'][i] < min_time:
            min_time = state['time_next_event'][i]
            state['next_event_type'] = i
    
    if state['next_event_type'] == 0:
        with open("mm1.out", "a") as f:
            f.write(f"\nEvent list empty at {state['sim_time']}")
        exit(1)
    
    state['sim_time'] = min_time

def arrive():
    state['time_next_event'][1] = state['sim_time'] + expon(state['mean_interarrival'])
    
    if state['server_status'] == BUSY:
        state['num_in_q'] += 1
        if state['num_in_q'] > Q_LIMIT:
            with open("mm1.out", "a") as f:
                f.write(f"\nQueue overflow at {state['sim_time']}")
            exit(2)
        state['time_arrival'][state['num_in_q']] = state['sim_time']
    else:
        state['total_of_delays'] += 0.0  # No delay for immediate service
        state['num_custs_delayed'] += 1
        state['server_status'] = BUSY
        state['time_next_event'][2] = state['sim_time'] + expon(state['mean_service'])

def depart():
    if state['num_in_q'] == 0:
        state['server_status'] = IDLE
        state['time_next_event'][2] = 1.0e30
    else:
        state['num_in_q'] -= 1
        delay = state['sim_time'] - state['time_arrival'][1]
        state['total_of_delays'] += delay
        state['num_custs_delayed'] += 1
        state['time_next_event'][2] = state['sim_time'] + expon(state['mean_service'])
        
        # Shift queue
        for i in range(1, state['num_in_q'] + 1):
            state['time_arrival'][i] = state['time_arrival'][i + 1]

def update_time_avg_stats():
    time_since = state['sim_time'] - state['time_last_event']
    state['time_last_event'] = state['sim_time']
    
    state['area_num_in_q'] += state['num_in_q'] * time_since
    state['area_server_status'] += state['server_status'] * time_since

def report():
    with open("mm1.out", "w") as f:
        f.write(f"""
        Single-server Queue System Results
        {'='*40}
        Mean interarrival time: {state['mean_interarrival']:.3f} mins
        Mean service time: {state['mean_service']:.3f} mins
        Customers requested: {state['num_delays_required']}
        
        Average delay: {state['total_of_delays']/state['num_custs_delayed']:.3f} mins
        Average queue length: {state['area_num_in_q']/state['sim_time']:.3f}
        Server utilization: {state['area_server_status']/state['sim_time']:.3f}
        Simulation end time: {state['sim_time']:.3f} mins
        """)

def main():
    # Read input with error handling
    try:
        with open("mm1.in", "r") as f:
            lines = [line.split('#')[0].strip() for line in f]
            params = ' '.join(lines).split()
            
        state['mean_interarrival'] = float(params[0])
        state['mean_service'] = float(params[1])
        state['num_delays_required'] = int(params[2])
    except Exception as e:
        print(f"Error reading input: {str(e)}")
        exit(1)

    initialize()
    
    # Run simulation with safety check
    max_events = 100_000
    event_count = 0
    
    while state['num_custs_delayed'] < state['num_delays_required']:
        timing()
        update_time_avg_stats()
        
        if state['next_event_type'] == 1:
            arrive()
        else:
            depart()
        
        # Prevent infinite loop
        event_count += 1
        if event_count > max_events:
            print("Emergency break: Too many events!")
            with open("mm1.out", "a") as f:
                f.write("\nSimulation interrupted - infinite loop suspected")
            break

    report()
    print("Simulation complete. Results written to mm1.out")

if __name__ == "__main__":
    main()