import random

winning_msg = "Congratulations, you win the car!"
loosing_msg = "It is the goat"
possible_numbers = "123"

# asks how many rounds do you want to play
game_cycle = input("How often do you want to play this game?: ")
# asks if you always want to switch to the suggested door
always_change = input("Do you always want to switch doors? (y/n): ")
# current_round
roundnumber = 0

# loop for the game rounds
for roundnumber in range(0, int(game_cycle)):
    # gets door
    chosen_door = input("Which door do you choose? (1, 2, 3): ")
    print("We are opening the door number " + chosen_door + " for you.")
    # program decides winning door
    winning_door = random.choice(possible_numbers)
    # checks if door is winning door
    if (winning_door == chosen_door):
        print(winning_msg)
    else:
        print(loosing_msg)
        # chooses suggested door
        while True:
            next_door = random.choice(possible_numbers)
            # checks if the suggested door isn't the the same door we chose before
            if (next_door != chosen_door):
                break
        # skipped question
        if (always_change == "y"):
            print("Automatically switching to door " + next_door)
            if (winning_door == next_door):
                print(winning_msg)
            else:
                print(loosing_msg)
        else:
            # asks if you want to change the chosen door
            change_door = input("Do you wanna change to door " + next_door + "? (y/n)")
            # checks if you want to change the door
            if (change_door == "y"):
                if (winning_door == next_door):
                    print(winning_msg)
                else:
                    print(loosing_msg)
            else:
                print(loosing_msg)

    # increments roundnumber
    roundnumber =+ 1
