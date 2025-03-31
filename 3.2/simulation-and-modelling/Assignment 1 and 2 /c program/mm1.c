/* External definitions for single-server queueing system. */
#include <stdio.h>
#include <math.h>
#include "logrand.h" /* Header file for random-number generator. */

#define Q_LIMIT 100 /* Limit on queue length. */
#define BUSY 1 /* Mnemonics for server's being busy */
#define IDLE 0 /* and idle. */

int next_event_type, num_custs_delayed, num_delays_required, num_events,
    num_in_q, server_status;
float area_num_in_q, area_server_status, mean_interarrival, mean_service,
    sim_time, time_arrival[Q_LIMIT + 1], time_last_event, time_next_event[3],
    total_of_delays;
FILE *infile, *outfile;

void initialize(void);
void timing(void);
void arrive(void);
void depart(void);
void report(void);
void update_time_avg_stats(void);
float expon(float mean);

/* Main function */
main() {
    /* Open input and output files. */
    infile = fopen("mml.in", "r");
    outfile = fopen("mml.out", "w");
    
    /* Specify the number of events for the timing function. */
    num_events = 2;
    
    /* Read input parameters. */
    fscanf(infile, "%f %f %d", &mean_interarrival, &mean_service, &num_delays_required);
    
    /* Write report heading and input parameters. */
    fprintf(outfile, "Single-server queueing system\n\n");
    fprintf(outfile, "Mean interarrival time%11.3f minutes\n\n", mean_interarrival);
    fprintf(outfile, "Mean service time%16.3f minutes\n\n", mean_service);
    fprintf(outfile, "Number of customers%14d\n\n", num_delays_required);
    
    /* Initialize the simulation. */
    initialize();
    
    /* Run the simulation while more delays are still needed. */
    while (num_custs_delayed < num_delays_required) {
        /* Determine the next event. */
        timing();
        
        /* Update time-average statistical accumulators. */
        update_time_avg_stats();
        
        /* Invoke the appropriate event function. */
        switch (next_event_type) {
            case 1: 
                arrive();
                break;
            case 2: 
                depart();
                break;
        }
    }
    
    /* Invoke the report generator and end the simulation. */
    report();
    
    fclose(infile);
    fclose(outfile);
    return 0;
}

/* Initialization function */
void initialize(void) {
    /* Initialize the simulation clock. */
    sim_time = 0.0;
    
    /* Initialize the state variables. */
    server_status = IDLE;
    num_in_q = 0;
    time_last_event = 0.0;
    
    /* Initialize the statistical counters. */
    num_custs_delayed = 0;
    total_of_delays = 0.0;
    area_num_in_q = 0.0;
    area_server_status = 0.0;
    
    /* Initialize event list. */
    time_next_event[1] = sim_time + expon(mean_interarrival);
    time_next_event[2] = 1.0e+30;
}

/* Timing function */
void timing(void) {
    int i;
    float min_time_next_event = 1.0e+29;
    next_event_type = 0;
    
    /* Determine the next event type. */
    for (i = 1; i <= num_events; ++i) {
        if (time_next_event[i] < min_time_next_event) {
            min_time_next_event = time_next_event[i];
            next_event_type = i;
        }
    }
    
    /* Check for event list empty. */
    if (next_event_type == 0) {
        fprintf(outfile, "\nEvent list empty at time %f", sim_time);
        exit(1);
    }
    
    /* Advance the simulation clock. */
    sim_time = min_time_next_event;
}

/* Arrival event function */
void arrive(void) {
    float delay;
    
    /* Schedule next arrival. */
    time_next_event[1] = sim_time + expon(mean_interarrival);
    
    /* Check if server is busy. */
    if (server_status == BUSY) {
        ++num_in_q;
        
        /* Check for overflow. */
        if (num_in_q > Q_LIMIT) {
            fprintf(outfile, "\nOverflow at time %f", sim_time);
            exit(2);
        }
        time_arrival[num_in_q] = sim_time;
    } else {
        delay = 0.0;
        total_of_delays += delay;
        ++num_custs_delayed;
        server_status = BUSY;
        time_next_event[2] = sim_time + expon(mean_service);
    }
}

/* Departure event function */
void depart(void) {
    int i;
    float delay;
    
    /* Check if queue is empty. */
    if (num_in_q == 0) {
        server_status = IDLE;
        time_next_event[2] = 1.0e+30;
    } else {
        --num_in_q;
        delay = sim_time - time_arrival[1];
        total_of_delays += delay;
        ++num_custs_delayed;
        time_next_event[2] = sim_time + expon(mean_service);
        
        /* Shift queue entries. */
        for (i = 1; i <= num_in_q; ++i) {
            time_arrival[i] = time_arrival[i + 1];
        }
    }
}

/* Report generator function */
void report(void) {
    fprintf(outfile, "\n\nAverage delay in queue%11.3f minutes\n\n",
            total_of_delays / num_custs_delayed);
    fprintf(outfile, "Average number in queue%10.3f\n\n",
            area_num_in_q / sim_time);
    fprintf(outfile, "Server utilization%15.3f\n\n",
            area_server_status / sim_time);
    fprintf(outfile, "Time simulation ended%12.3f minutes", sim_time);
}

/* Update time averages */
void update_time_avg_stats(void) {
    float time_since_last_event = sim_time - time_last_event;
    time_last_event = sim_time;
    
    area_num_in_q += num_in_q * time_since_last_event;
    area_server_status += server_status * time_since_last_event;
}

/* Exponential variate generation */
float expon(float mean) {
    return -mean * log(logrand(1));
}