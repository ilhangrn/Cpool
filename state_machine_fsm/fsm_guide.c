#include <stdio.h>
//Different state of ATM machine
typedef enum
{
    idle_state,
    card_inserted_state,
    last_state
} system_state_t;

//Different type events
typedef enum
{
    card_insert_event,
    card_remove_event,
    last_event
} system_event_t;

//typedef of function pointer
typedef system_state_t (*event_handler)(void);

//structure of state and event with event handler
typedef struct
{
    system_state_t system_state;
    system_event_t system_event;
    event_handler state_event_handler;
} fsm_t;


//function call to processing track data and return card inserted state
system_state_t insert_card_handler(void)
{
    return card_inserted_state;
}

//function call to processing track data and return card inserted state
system_state_t remove_card_handler(void)
{
    return idle_state;
}

//Initialize array of structure with states and event with proper handler
fsm_t fsm [] =
{
    {idle_state,card_insert_event,insert_card_handler},
    {card_inserted_state,card_remove_event,remove_card_handler},
};

//main function
int main()
{
    system_state_t next_state = idle_state;
    while(1)
    {
        //Api read the event
        system_event_t new_event = read_event();
        if((next_state < last_state) && (new_event < last_event)&& (fsm[next_state].system_event == new_event) && (fsm[next_state].state_event_handler != NULL))
        {
            // function call as per the state and event and return the next state of the finite state machine
            next_state = (*fsm[next_state].state_event_handler)();
        }
        else
        {
            //Invalid
        }
    }
    return 0;
}