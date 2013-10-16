/*-------------------------------------------------------------------------
 * Programmer: Xiaotian Lu,George Wang
 * Date: 3/21/2012
 * Name: HW3.c
 * Description: This program is about a 3pi robot accociate
 *              with Homework 3 due on 3/21/2012
 *              For the homework
 -------------------------------------------------------------------------*/


/*---------------------------------------------------------------------------------------------------------
Pseudocode Description
The program has three strageties to permore. The first one is Proportional controller for line following,
The supplied version of the program uses a simple proportional control strategy to follow the track, based
upon readings from the reflective sensors. This code independently adjusts the speed of the left and right
motors depending on the sensor inputs. that readline function gives a value from 0 to 4000, depending on
the robot¡¯s position of the track with respect to the sensors.
Ifthe track is just beneath the central sensor, the reading will be 2000. If it is beneath the leftmost sensor,
the reading will be close to zero.
The second one is Proportional-Integral-Differential (PID) controller for line
following. The main idea is to predict the
future value of proportional using its current and past values; the prediction can be used to precompensate
for future errors, thus improving the ability of the robot to go around sharp corners. For
example, the difference between the current and the immediately previous value of proportional
(termed as derivative= proportional-oldproportional) denotes the rate of change.
This measure can be used to predict the value of proportional at the next loop index.
----------------------------------------------------------------------------------------------------------*/





// The 3pi include file must be at the beginning of any program that
// uses the Pololu AVR library and 3pi.
#include <pololu/3pi.h>

// This include file allows data to be stored in program space.  The
// ATmega168 has 16k of program space compared to 1k of RAM, so large
// pieces of static data should be stored in program space.
#include <avr/pgmspace.h>
// Introductory messages.  The "PROGMEM" identifier causes the data to
// go into program space.
const char welcome_line1[] PROGMEM = " Pololu";
const char welcome_line2[] PROGMEM = "3\xf7 Robot";
const char demo_name_line1[] PROGMEM = "PID Line";
const char demo_name_line2[] PROGMEM = "follower";
const char firstline[] PROGMEM = " slect str";
const char firstline1[] PROGMEM = " S1S2S3";
// A couple of simple tunes, stored in program space.
const char welcome[] PROGMEM = ">g32>>c32";
const char go[] PROGMEM = "L16 cdegreg4";

const char increase[] PROGMEM = "L16 dd";
const char decrease[] PROGMEM = "L16 bb";

void run_proportional(int proportional, int speed);
void initialize();
int input_gear(int gear);

// Data for generating the characters used in load_custom_characters
// and display_readings.  By reading levels[] starting at various
// offsets, we can generate all of the 7 extra characters needed for a
// bargraph.  This is also stored in program space.
const char levels[] PROGMEM = {
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b00000,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111,
	0b11111
};


// This function loads custom characters into the LCD.  Up to 8
// characters can be loaded; we use them for 7 levels of a bar graph.
void load_custom_characters()
{
	lcd_load_custom_character(levels+0,0); // no offset, e.g. one bar
	lcd_load_custom_character(levels+1,1); // two bars
	lcd_load_custom_character(levels+2,2); // etc...
	lcd_load_custom_character(levels+3,3);
	lcd_load_custom_character(levels+4,4);
	lcd_load_custom_character(levels+5,5);
	lcd_load_custom_character(levels+6,6);
	clear(); // the LCD must be cleared for the characters to take effect
}


void run_pid(int proportional, int derivative, int integral, int speed);
int run_pid2(int proportional, int derivative, int integral, int mean, int speed);




// This function displays the sensor readings using a bar graph.
void display_readings(const unsigned int *calibrated_values)
{
	unsigned char i;

	for(i=0;i<5;i++) {
		// Initialize the array of characters that we will use for the
		// graph.  Using the space, an extra copy of the one-bar
		// character, and character 255 (a full black box), we get 10
		// characters in the array.
		const char display_characters[10] = {' ',0,0,1,2,3,4,5,6,255};

		// The variable c will have values from 0 to 9, since
		// calibrated values are in the range of 0 to 1000, and
		// 1000/101 is 9 with integer math.
		char c = display_characters[calibrated_values[i]/101];

		// Display the bar graph character.
		print_character(c);
	}
}


// Initializes the 3pi, displays a welcome message, calibrates, and
// plays the initial music.
void initialize()
{
	unsigned int counter; // used as a simple timer
	unsigned int sensors[5]; // an array to hold sensor values

	// This must be called at the beginning of 3pi code, to set up the
	// sensors.  We use a value of 2000 for the timeout, which
	// corresponds to 2000*0.4 us = 0.8 ms on our 20 MHz processor.
	pololu_3pi_init(2000);
	load_custom_characters(); // load the custom characters

	// Play welcome music and display a message
	print_from_program_space(welcome_line1);
	lcd_goto_xy(0,1);
	print_from_program_space(welcome_line2);
	play_from_program_space(welcome);
	delay_ms(1000);

	clear();
	print_from_program_space(demo_name_line1);
	lcd_goto_xy(0,1);
	print_from_program_space(demo_name_line2);
	delay_ms(1000);

	// Display battery voltage and wait for button press
	while(!button_is_pressed(BUTTON_B))
	{
		int bat = read_battery_millivolts();

		clear();
		print_long(bat);
		print("mV");
		lcd_goto_xy(0,1);
		print("Press B");

		delay_ms(100);
	}

	// Always wait for the button to be released so that 3pi doesn't
	// start moving until your hand is away from it.
	wait_for_button_release(BUTTON_B);
	delay_ms(1000);

	// Auto-calibration: turn right and left while calibrating the
	// sensors.
	for(counter=0;counter<80;counter++)
	{
		if(counter < 20 || counter >= 60)
			set_motors(40,-40);
		else
			set_motors(-40,40);

		// This function records a set of sensor readings and keeps
		// track of the minimum and maximum values encountered.  The
		// IR_EMITTERS_ON argument means that the IR LEDs will be
		// turned on during the reading, which is usually what you
		// want.
		calibrate_line_sensors(IR_EMITTERS_ON);

		// Since our counter runs to 80, the total delay will be
		// 80*20 = 1600 ms.
		delay_ms(20);
	}
	set_motors(0,0);

}




//-------------------------------------------------------------------
// This is the main function, where the code starts.  All C programs
// must have a main() function defined somewhere.
//-------------------------------------------------------------------
int main()
{
	unsigned int sensors[5]={0}; // an array to hold sensor values
	unsigned int last_proportional=0;
	int i;                       //for loop counter
	int mean;                    //for the proportinal mean
	int proportional=0;
    int derivative=0;
    int lap_index=-1;                   // starts the lap when the mark orthogonal to the track is detected
	long integral=0;
    int gear = 2;                       // default gear
    unsigned long start_time;           // variable to store the starting time
                                        // used for timing

     clear();
    lcd_goto_xy(0,0);
    print_from_program_space(firstline);
    lcd_goto_xy(0,1);
    print_from_program_space(firstline1);

    unsigned char button1 = wait_for_button (ANY_BUTTON);
    if(button1 == BUTTON_A)
    {




    // set up the 3pi
	initialize();

    // Allows user to change gears using buttons.
    //--------------------------------------------

    gear = input_gear(gear);


    // Start the program.
    //--------------------

    clear();
	print("Go!");

	// Play music and wait for it to finish before we start driving.
	play_from_program_space(go);
	while(is_playing());//play music

    unsigned long time = get_ms();

    // This is the "main loop" - it will run forever.
	while(1)
	{

        // Get the position of the line.
		unsigned int position = read_line(sensors,IR_EMITTERS_ON);


		// The "proportional" term should be 0 when we are on the line.
		proportional = ((int)position) - 2000;
		derivative = proportional - last_proportional;
		integral += proportional;
		last_proportional = proportional;



        switch (gear)
        {
            case 1:   run_proportional(proportional, 64);
                break;
            case 2:   run_proportional(proportional, 128);
                break;
            case 3:   run_proportional(proportional, 164);
                break;
            case 4:   run_proportional(proportional, 192);
                break;
            case 5:   run_proportional(proportional, 255);
                break;
        }



        // Increase lap index if all sensors are active; i.e., mark has been reached
        //---------------------------------------------------------------------------
        if (sensors[0]>400 && sensors[1]>400 && sensors[2]>400 && sensors[3]>400 && sensors[4]>400 && (get_ms()-time)>100)
        {
            lap_index++;
            time = get_ms();
        }

        if(lap_index == 0)           // First mark: set the start time
        {
            start_time = time;
        }
        else if (lap_index == 1 ) {  // Terminate and wait indefinitely in while loop if total number of laps exceed 1
            set_motors(0,0);
            clear();
            left_led(0);
            right_led(0);
            position = read_line(sensors,IR_EMITTERS_OFF);

            lcd_goto_xy(0,0);
            print("RUN TIME");
            lcd_goto_xy(0,1);
            print_long(get_ms() - start_time);
            while(1);
        }

    }
	// This part of the code is never reached.  A robot should
	// never reach the end of its program, or unpredictable behavior
	// will result as random code starts getting executed.  If you
	// really want to stop all actions at some point, set your motors
	// to 0,0 and run the following command to loop forever:
	//
	 while(1);

}


    else if(button1 == BUTTON_B)
    {


    // set up the 3pi
	initialize();

    // Allows user to change gears using buttons.
    //--------------------------------------------

    gear = input_gear(gear);

    // Start the program.
    //--------------------

    clear();
	print("Go!");

	// Play music and wait for it to finish before we start driving.
	play_from_program_space(go);
	while(is_playing());

    unsigned long time = get_ms();

    // This is the "main loop" - it will run forever.
	while(1)
	{

        // Get the position of the line.
		unsigned int position = read_line(sensors,IR_EMITTERS_ON);


		// The "proportional" term should be 0 when we are on the line.
		proportional = ((int)position) - 2000;
		derivative = proportional - last_proportional;
		integral += proportional;
		last_proportional = proportional;


        // CALL PROPORTIONAL CONTROLLER WITH DIFFERENT SPEED SETTINGS
        //------------------------------------------------------------

        switch (gear)
        {
            case 1:   run_pid(proportional, derivative, integral, 64);
                break;
            case 2:   run_pid(proportional, derivative, integral, 128);
                break;
            case 3:   run_pid(proportional, derivative, integral, 169);
                break;
            case 4:   run_pid(proportional, derivative, integral, 222);
                break;
            case 5:   run_pid(proportional, derivative, integral, 350);
                break;
        }



        // Increase lap index if all sensors are active; i.e., mark has been reached
        //---------------------------------------------------------------------------
        if (sensors[0]>400 && sensors[1]>400 && sensors[2]>400 && sensors[3]>400 && sensors[4]>400 && (get_ms()-time)>100)
        {
            lap_index++;
            time = get_ms();
        }

        if(lap_index == 0)           // First mark: set the start time
        {
            start_time = time;
        }
        else if (lap_index == 1 ) {  // Terminate and wait indefinitely in while loop if total number of laps exceed 1
            set_motors(0,0);
            clear();
            left_led(0);
            right_led(0);
            position = read_line(sensors,IR_EMITTERS_OFF);

            lcd_goto_xy(0,0);
            print("RUN TIME");
            lcd_goto_xy(0,1);
            print_long(get_ms() - start_time);
            while(1);
        }

     }
    }
    else if(button1 == BUTTON_C)
    {


    int *pro ;//set a pointer
    int speed=200;
    pro = (int *) malloc(20 * sizeof(int));//dynamicly set the memory

    // set up the 3pi
	initialize();

    // Start the program.
    //--------------------

    clear();// claer led
	print("Go!");

	// Play music and wait for it to finish before we start driving.
	play_from_program_space(go);
	while(is_playing());

    unsigned long time = get_ms();

    // This is the "main loop" - it will run forever.
	while(1)
	{

        // Get the position of the line.
		unsigned int position = read_line(sensors,IR_EMITTERS_ON);


		// The "proportional" term should be 0 when we are on the line.
		proportional = ((int)position) - 2000;
		derivative = proportional - last_proportional;
		integral += proportional;
		last_proportional = proportional;

        mean = 0;
        pro[0]=proportional;
        for(i=0;i<20;i++)
        {
            mean = pro[i]+ mean;
            pro[i+1]=pro[i];
        }
        mean = mean/20;




        speed=run_pid2(proportional, derivative, integral, mean, speed);//speed change of second strategy



        // Increase lap index if all sensors are active; i.e., mark has been reached
        //---------------------------------------------------------------------------
        if (sensors[0]>400 && sensors[1]>400 && sensors[2]>400 && sensors[3]>400 && sensors[4]>400 && (get_ms()-time)>100)
        {
            lap_index++;
            time = get_ms();
        }

        if(lap_index == 0)           // First mark: set the start time
        {
            start_time = time;
        }
        else if (lap_index == 1 ) {  // Terminate and wait indefinitely in while loop if total number of laps exceed 1
            set_motors(0,0);
            clear();
            left_led(0);
            right_led(0);
            position = read_line(sensors,IR_EMITTERS_OFF);

            lcd_goto_xy(0,0);
            print("RUN TIME");
            lcd_goto_xy(0,1);
            print_long(get_ms() - start_time);
            while(1);
        }
    }
	// This part of the code is never reached.  A robot should
	// never reach the end of its program, or unpredictable behavior
	// will result as random code starts getting executed.  If you
	// really want to stop all actions at some point, set your motors
	// to 0,0 and run the following command to loop forever:
	//
	 while(1);

}
}//end main

//--------------------------------------------------------------------------------------
// This is the main line following code. It sets the speed of the individual motors to
// speed + powerdiff and speed - powerdiff. Here, powerdiff is determined as
// the current error weighted by 128/2000.
// The motor speeds are always restricted to be in the range [0,255]
//--------------------------------------------------------------------------------------

void run_proportional(int proportional, int speed)
{

    float factor = 128/2000.0; // factor tuned so that proportional*factor in [-128,128]
    float computed = (float)(proportional);
    int power_difference = (int)(computed*factor);

    // Compute the actual motor settings.  We never set either motor
    // to a negative value or greater than 255.

    int lspeed = speed + 3*-power_difference;
    int rspeed = speed - 3*power_difference;

    if(lspeed < 0)   lspeed = 0;
    if(rspeed < 0)   rspeed = 0;
    if(lspeed > 255) lspeed = 255;
    if(rspeed > 255) rspeed = 255;

    set_motors(lspeed, rspeed);

    return;
}


//--------------------------------------------------------------------------------------
// This function allows the users to increase or decrease the gears using the buttons
//--------------------------------------------------------------------------------------

int input_gear(int gear)
{
    unsigned char buttons = BUTTON_A;


    clear();
    lcd_goto_xy(0,0);
    print("A:< gear");
    lcd_goto_xy(0,1);
    print("C:> gear");
    delay_ms(1000);
    clear();
    lcd_goto_xy(0,0);
    print("B:OK");
    lcd_goto_xy(0,1);
    print("Gear "); print_long(gear);


    buttons = wait_for_button(ANY_BUTTON);
    while (buttons != BUTTON_B)
    {
        if (buttons == BUTTON_C) {
            gear = gear + 1;
            if(gear >5)  gear = 5;
            clear(); lcd_goto_xy(0,0); print("<  OK  >");
            lcd_goto_xy(0,1); print("Gear "); print_long(gear);
        }
        else
        {
            gear = gear - 1;
            if (gear<1) gear = 1;
            clear(); lcd_goto_xy(0,0); print("<  OK  >");
            lcd_goto_xy(0,1); print("Gear "); print_long(gear);
        }

    buttons = wait_for_button(ANY_BUTTON);
    }
    return(gear);

}

/*------------------------------------------------------------
This function is strage 2, it can predict the fucture value
of propotional, the function will generate the drivative, integral
which are the previous and sum of the past values
then use equation:
power_difference = proportional + integral*0.001 + derivative*20.0;
to get the constant
 ------------------------------------------------------------*/

void run_pid(int proportional, int derivative, int integral, int speed)
{


    int power_difference;//initialize the power

    power_difference = proportional + integral*0.001 + derivative*20.0;//set the power by this given equation

    int lspeed = speed + power_difference;//initialize the left speed
    int rspeed = speed - power_difference;//initialize the left speed

    // Compute the actual motor settings.  We never set either motor
    // to a negative value or greater than 255. we change the value that it will run faster

    if(lspeed < 0)   lspeed = 0;
    if(rspeed < 0)   rspeed = 0;
    if(lspeed > 400) lspeed = 400;
    if(rspeed > 400) rspeed = 400;

    set_motors(lspeed, rspeed);

    return;

}

/*------------------------------------------------------------
This function is strage 3, it can predict the fucture value
of propotional,and get the mean from the past 20 proportional value
and compare to a desired position to increase or decrease the speed.
 the function will generate the drivative, integral
which are the previous and sum of the past values
then use equation:
power_difference = proportional + integral*0.001 + derivative*20.0;
to get the constant
input: proportinal, derivative, integral , mean , speed
output: speed
 ------------------------------------------------------------*/

int run_pid2(int proportional, int derivative, int integral, int mean, int speed)
{

    int lspeed=speed;
    int rspeed=speed; //set the motor speed to be the input speed
    int power_difference; // the speed that the robot turns

    //when the average of the past 20 proportional is greater than -500 and less than 500 , increase the speed by 20
    if( (-500<mean) && (mean<500) )
    {
        lspeed += 20;
        rspeed += 20;
        power_difference = (proportional + integral*0.001 + derivative*20.0);
    }
    //when the average of the past 20 proportional is greater than 700 or less than -700 , decrease the speed by 50
    if( (mean<-700) || (mean> 700))
    {
        lspeed -= 50;
        rspeed -= 50;
        power_difference = 1.5*(proportional + integral*0.001 + derivative*20.0);
    }




    lspeed = lspeed + power_difference;
    rspeed = rspeed - power_difference;

    if(lspeed < 0)   lspeed = 0;
    if(rspeed < 0)   rspeed = 0;
    if(lspeed > 500) lspeed = 500;
    if(rspeed > 500) rspeed = 500;


    set_motors(lspeed, rspeed);
    speed= (lspeed+rspeed)/2; //set the speed to be the mean of the two motor speed

    return speed; //return speed back to the while loop
}
