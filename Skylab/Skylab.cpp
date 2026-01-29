// Skylab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>
#include <algorithm>

#include "StepperUnit.h"
#include "Relay.h"
#include "Solenoids.h"

int main()
{

    Solenoids::change = true;

    enum strictness {Liberal, Conservitive};

    // Adjustments
    int c25_adj = 5;
    int c10_adj = 1;
    int c5_adj = 2;
    int ball_3_5_adj = 5;
	int spacelabRocketSpecial_adj = 1;
	bool match_adj = false;
	strictness spaceLab_adj = Liberal;

    const int reA                 = 0;
    const int reB                 = 1;
    const int reBallIndex         = 2;
    const int reBonus             = 3;
    const int reCaptiveBall       = 4;
    const int reChange            = 5;
    const int reCoin              = 6;
    const int reDoubleBonus       = 7;
    const int reFiveBallInline    = 8;
    const int reC5                = 9;
    const int reC10               = 10;
    const int reC25               = 11;
    const int rePt50              = 12;
    const int reGameOver          = 13;
    const int reGame              = 14;
    const int rePt100000          = 15;
    const int reOutHole           = 16;
    const int reK                 = 17;
    const int reL                 = 18;
    const int reLock              = 19;
    const int reReset             = 20;
    const int reRocketSpecial     = 21;
    const int reS                 = 22;
    const int reScoreReset        = 23;
    const int reSkyLab            = 24;
    const int reSkylabBankReset   = 25;
    const int reSpaceLab          = 26;
    const int reSpaceLabSpecial   = 27;
    const int rePt10              = 28;
    const int rePt100             = 29;
    const int rePt1000            = 30;
    const int reY                 = 31;

    Relay re[reY + 1];

	re[reA] = Relay("a", Relay::RelayType);
	re[reB] = Relay("b", Relay::RelayType);
	re[reBallIndex] = Relay("ballIndex", Relay::RelayType);
	re[reBonus] = Relay("bonus", Relay::RelayType);
	re[reCaptiveBall] = Relay("captiveBall", Relay::RelayType);
	re[reChange] = Relay("change", Relay::RelayType);
	re[reCoin] = Relay("coin", Relay::RelayType);
	re[reDoubleBonus] = Relay("doubleBonus", Relay::RelayType);
	re[reFiveBallInline] = Relay("fiveBallInline", Relay::RelayType);
	re[reC5] = Relay("c5", Relay::RelayType);
	re[reC10] = Relay("c10", Relay::RelayType);
	re[reC25] = Relay("c25", Relay::RelayType);
	re[rePt50] = Relay("pt50", Relay::RelayType);
	re[reGameOver] = Relay("gameOver", Relay::RelayType);
	re[reGame] = Relay("game", Relay::RelayType);
	re[rePt100000] = Relay("pt100000", Relay::RelayType);
	re[reOutHole] = Relay("outHole", Relay::RelayType);
	re[reK] = Relay("k", Relay::RelayType);
	re[reL] = Relay("l", Relay::RelayType);
	re[reLock] = Relay("lock", Relay::RelayType);
	re[reReset] = Relay("reset", Relay::RelayType);
	re[reRocketSpecial] = Relay("rocketSpecial", Relay::RelayType);
	re[reS] = Relay("s", Relay::RelayType);
	re[reScoreReset] = Relay("scoreReset", Relay::RelayType);
	re[reSkyLab] = Relay("skyLab", Relay::RelayType);
	re[reSkylabBankReset] = Relay("skylabBankReset", Relay::RelayType);
	re[reSpaceLab] = Relay("spaceLab", Relay::RelayType);
	re[reSpaceLabSpecial] = Relay("spaceLabSpecial", Relay::RelayType);
	re[rePt10] = Relay("pt10", Relay::RelayType);
	re[rePt100] = Relay("pt100", Relay::RelayType);
	re[rePt1000] = Relay("pt1000", Relay::RelayType);
	re[reY] = Relay("y", Relay::RelayType);

    const int reSize = std::size(re);

    Relay reAs[reSize];

    for (int i=0; i < reSize; ++i)
    {
        reAs[i] = Relay(re[i]);
	}

    bool impulse = false;

    const int advanceCount  = 0;
    const int alternator    = 1;
    const int ballCount     = 2;
    const int noMatch       = 3;
    const int credit        = 4;
    const int pt10          = 5;
    const int pt100         = 6;
    const int pt1000        = 7;
    const int pt10000       = 8;
    const int scoreMotor    = 9;

    StepperUnit units[scoreMotor + 1];
	units[advanceCount] = StepperUnit("advanceCount", 9);
	units[alternator] = StepperUnit("alternator", 2);
	units[ballCount] = StepperUnit("ballCount", 5, StepperUnit::UpDown);
	units[noMatch] = StepperUnit("noMatch", 10, StepperUnit::Continuous);
	units[credit] = StepperUnit("credit", 9, StepperUnit::UpDown);
	units[pt10] = StepperUnit("pt10", 9, StepperUnit::Continuous);
	units[pt100] = StepperUnit("pt100", 9, StepperUnit::Continuous);
	units[pt1000] = StepperUnit("pt1000", 9, StepperUnit::Continuous);
	units[pt10000] = StepperUnit("pt10000", 9, StepperUnit::Continuous);
	units[scoreMotor] = StepperUnit("scoreMotor", 5, StepperUnit::Continuous);

    const int unitsSize = std::size(units);
    StepperUnit unitsA[unitsSize];
    for (int i = 0; i < unitsSize; ++i)
    {
        unitsA[i] = StepperUnit(units[i]);
    }

    // Alternator Unit
    int alternatorUnit = 0;             // E-2
    bool altUnit_eos = false;          // TODO: altUnit_eos - Don't know what value;

    // SkyLab Unit Stepper
    bool skyLabResetUnit = false;      // D-1

	const int solBallRelease = 0;
	const int solCoinLockout = 1;
	const int solKnocker = 2;
	const int solLeftFlipper = 3;
	const int solLeftJetBumper = 4;
	const int solLargeChime = 5;
	const int solMediumChime = 6;
	const int solSmallChime = 7;
	const int solTotalPaymeter = 8;

	Relay sol[solTotalPaymeter + 1];

	sol[solBallRelease] = Relay("ballRelease", Relay::Solenoid);
	sol[solCoinLockout] = Relay("coinLockout", Relay::Solenoid);
	sol[solKnocker] = Relay("knocker", Relay::Solenoid);
	sol[solLeftFlipper] = Relay("leftFlipper", Relay::Solenoid);
	sol[solLeftJetBumper] = Relay("leftJetBumper", Relay::Solenoid);
	sol[solLargeChime] = Relay("largeChime", Relay::Solenoid);
	sol[solMediumChime] = Relay("mediumChime", Relay::Solenoid);
	sol[solSmallChime] = Relay("smallChime", Relay::Solenoid);
	sol[solTotalPaymeter] = Relay("totalPaymeter", Relay::Solenoid);

	int solenoidsSize = std::size(sol);
	Relay priorSol[solTotalPaymeter + 1];

    // Switches
    const int tilt_sw               = 0;
    const int kickOff_sw            = 1;
    const int leftFlipper_sw        = 2; // C-16 (2)
    const int c25_sw                = 3;          // D-2
    const int c10_sw                = 4;          // D-2
    const int c5_sw                 = 5;           // D-3
    const int antiCheat_sw          = 6;    // C-2
    const int creditButton_sw       = 7; // E-3
	const int sStandup_sw           = 8;     // E-10
    const int kStandup_sw           = 9;     // E-11
    const int yStandup_sw           = 10;     // E-11
    const int lStandup_sw           = 11;     // E-11
    const int aStandup_sw           = 12;     // E-11
    const int bStandup_sw           = 13;     // E-11
    const int outHole_sw            = 14; // D-9
	const int right1CaptiveBall_sw  = 15; // D-12
	const int left1CaptiveBall_sw   = 16;  // D-12
    const int right2CaptiveBall_sw  = 17; // D-12
    const int left2CaptiveBall_sw   = 18;  // D-12
    const int right3CaptiveBall_sw  = 19; // D-12
    const int left3CaptiveBall_sw   = 20;  // D-12
    const int right4CaptiveBall_sw  = 21; // D-12
    const int left4CaptiveBall_sw   = 22;  // D-12
	const int leftBotOutsideRollover_sw = 23; // D-13
    const int rightBotOutsideRollover_sw = 24; // D-13
	const int leftKickerCount_sw    = 25; // D-13
	const int rightKickerCount_sw   = 26; // D-13
    const int leftJetBumper_sw      = 27; // E-14
	const int rightJetBumper_sw     = 28; // E-14
    const int rightTopRollover_sw   = 29; // E-15
    const int leftTopRollover_sw    = 30;  // E-15
    const int rightBottomRollover_sw = 31; // E-15
	const int leftBottomRollover_sw = 32;  // E-15
    const int leftRolloverButton_sw = 33; // E-16
    const int rightRolloverButton_sw = 34; // E-16

    Relay sw[rightRolloverButton_sw + 1];

	sw[tilt_sw] = Relay("tilt", Relay::Switch);
	sw[kickOff_sw] = Relay("kickOff", Relay::Switch);
	sw[leftFlipper_sw] = Relay("leftFlipper", Relay::Switch);
	sw[c25_sw] = Relay("c25", Relay::Switch);
	sw[c10_sw] = Relay("c10", Relay::Switch);
	sw[c5_sw] = Relay("c5", Relay::Switch);
	sw[antiCheat_sw] = Relay("antiCheat", Relay::Switch);
	sw[creditButton_sw] = Relay("creditButton", Relay::Switch);
	sw[sStandup_sw] = Relay("sStandup", Relay::Switch);
	sw[kStandup_sw] = Relay("kStandup", Relay::Switch);
	sw[yStandup_sw] = Relay("yStandup", Relay::Switch);
	sw[lStandup_sw] = Relay("lStandup", Relay::Switch);
	sw[aStandup_sw] = Relay("aStandup", Relay::Switch);
	sw[bStandup_sw] = Relay("bStandup", Relay::Switch);
	sw[outHole_sw] = Relay("outHole", Relay::Switch);
	sw[right1CaptiveBall_sw] = Relay("right1CaptiveBall", Relay::Switch);
	sw[left1CaptiveBall_sw] = Relay("left1CaptiveBall", Relay::Switch);
	sw[right2CaptiveBall_sw] = Relay("right2CaptiveBall", Relay::Switch);
	sw[left2CaptiveBall_sw] = Relay("left2CaptiveBall", Relay::Switch);
	sw[right3CaptiveBall_sw] = Relay("right3CaptiveBall", Relay::Switch);
	sw[left3CaptiveBall_sw] = Relay("left3CaptiveBall", Relay::Switch);
	sw[right4CaptiveBall_sw] = Relay("right4CaptiveBall", Relay::Switch);
	sw[left4CaptiveBall_sw] = Relay("left4CaptiveBall", Relay::Switch);
	sw[leftBotOutsideRollover_sw] = Relay("leftBotOutsideRollover", Relay::Switch);
	sw[rightBotOutsideRollover_sw] = Relay("rightBotOutsideRollover", Relay::Switch);
	sw[leftKickerCount_sw] = Relay("leftKickerCount", Relay::Switch);
	sw[rightKickerCount_sw] = Relay("rightKickerCount", Relay::Switch);
	sw[leftJetBumper_sw] = Relay("leftJetBumper", Relay::Switch);
	sw[rightJetBumper_sw] = Relay("rightJetBumper", Relay::Switch);
	sw[rightTopRollover_sw] = Relay("rightTopRollover", Relay::Switch);
	sw[leftTopRollover_sw] = Relay("leftTopRollover", Relay::Switch);
	sw[rightBottomRollover_sw] = Relay("rightBottomRollover", Relay::Switch);
	sw[leftBottomRollover_sw] = Relay("leftBottomRollover", Relay::Switch);
	sw[leftRolloverButton_sw] = Relay("leftRolloverButton", Relay::Switch);
	sw[rightRolloverButton_sw] = Relay("rightRolloverButton", Relay::Switch);

    const int swSize = std::size(sw);
	
    Relay priorSw[swSize];


    // Odd Items


	for (int step = 0; step < 100; ++step)
    {
		// Topic: !!!! Step Control
        std::cout << "***** step = " << step << "\n";

		// Set prior switch states
        for (int i = 0; i < swSize; ++i)
        {
            priorSw[i].Assign(sw[i]);
        }

        // Topic: Outhole Test
        //{
        //    if (step == 0)
        //    {
        //        // Sets the initial conditions machine power up and started.
        //        reAs[reLock] = true;
        //        reAs[reCoin] = false;
        //        reAs[reGame] = true;
        //        reAs[reGameOver] = false;
        //        reAs[reReset] = false;
        //        reAs[reScoreReset] = false;
        //        unitsA[ballCount] = 0;
        //        unitsA[credit] = 5;
        //    }
        //    if (step == 3)
        //    {
        //        sw[outHole_sw] = true; // D-9
        //        unitsA[ballCount] = 5;
        //    }
        //    if (step == 12)
        //        sw[outHole_sw] = false; // D-9
        //}

		// Topic: K Standup Test
   //     {
   //         if (step == 0)
   //         {
   //             // Sets the initial conditions machine power up and started.
   //             reAs[reLock] = true;
   //             reAs[reCoin] = false;
   //             reAs[reGame] = true;
   //             reAs[reGameOver] = false;
   //             reAs[reReset] = false;
   //             reAs[reScoreReset] = false;
   //             unitsA[ballCount] = 0;
   //             unitsA[credit] = 5;
   //         }
   //         if (step == 3)
   //         {
   //             sw[kStandup_sw] = true;          // D-2
   //         }
   //         if (step == 5)
   //         {
   //             sw[kStandup_sw] = false;          // D-2
			//}

   //     }
        
        // Topic: SKYLAB Tests
        {
            if (step == 0)
            {
                // Sets the initial conditions machine power up and started.
                reAs[reLock] = true;
                reAs[reCoin] = false;
                reAs[reGame] = true;
                reAs[reGameOver] = false;
                reAs[reReset] = false;
                reAs[reScoreReset] = false;
                unitsA[ballCount] = 0;
                unitsA[credit] = 5;
            }
            if (step == 3)
            {
                sw[kStandup_sw]             = true;          // D-2
                sw[yStandup_sw]             = true;          // D-2
                sw[lStandup_sw]             = true;          // D-2
                sw[aStandup_sw]             = true;          // D-2
                sw[bStandup_sw]             = true;          // D-2
            }
            if (step == 5)
            {
                sw[kStandup_sw]             = false;          // D-2
                sw[yStandup_sw]             = false;          // D-2
                sw[lStandup_sw]             = false;          // D-2
                sw[aStandup_sw]             = false;          // D-2
                sw[bStandup_sw]             = false;          // D-2
            }
            if (step == 20)
            {
                sw[sStandup_sw] = true;          // D-2
            }
            if (step == 21)
            {
                sw[sStandup_sw] = false;          // D-2
            }
        }



            //sw[creditButton_sw] = true;          // E-3
            //sw[leftKickerCount_sw]      = true; // D-13
            //sw[rightKickerCount_sw]     = true; // D-13
            //sw[leftJetBumper_sw]        = true; // E-14
            //sw[rightJetBumper_sw]       = true; // E-14
            //sw[leftTopRollover_sw] = true;  // E-15  *****
            //sw[rightBottomRollover_sw]  = true; // E-15
            //sw[rightTopRollover_sw]     = true; // E-15
            //sw[leftBottomRollover_sw]   = true;  // E-15
            //sw[leftRolloverButton_sw]   = true; // E-16
            //sw[rightRolloverButton_sw]  = true; // E-16
        //}
        //if (step == 5)
        //{
			//sw[creditButton_sw] = false;          // E-3
            //sw[leftKickerCount_sw]      = false; // D-13
            //sw[rightKickerCount_sw]     = false; // D-13
            //sw[leftJetBumper_sw]        = false; // E-14
            //sw[rightJetBumper_sw]       = false; // E-14
            //sw[leftTopRollover_sw]      = false;  // E-15 *****
            //sw[rightBottomRollover_sw]  = false; // E-15
            //sw[rightTopRollover_sw]     = false; // E-15
            //sw[leftBottomRollover_sw]   = false;  // E-15
            //sw[leftRolloverButton_sw]   = false; // E-16
            //sw[rightRolloverButton_sw]  = false; // E-16
        //}
        //if (step == 7)
        //    sw[rightBottomRollover_sw] = true; // E-15
        //if (step == 9)
        //    sw[rightBottomRollover_sw] = false; // E-15

        //    sw[rightBottomRollover_sw] = true; // E-15

        //if (step == 15)
        //    sw[outHole_sw] = true; // D-9

        //    sw[rightBottomRollover_sw] = false; // E-15
        //if (step == 17)
        //    sw[outHole_sw] = false; // D-9
        //    sw[rightBottomRollover_sw] = true; // E-15

        
        //    sw[rightBottomRollover_sw] = false; // E-15
        //if (step == 19)
        //    sw[rightBottomRollover_sw] = true; // E-15
        //if (step == 21)
        //    sw[rightBottomRollover_sw] = false; // E-15
        //if (step == 25)
        //    sw[outHole_sw] = true;
        //if (step == 23)
        //    sw[rightBottomRollover_sw] = true; // E-15
        //if (step == 25)
        //    sw[rightBottomRollover_sw] = false; // E-15
        //if (step == 27)
        //    sw[rightBottomRollover_sw] = true; // E-15
        //if (step == 29)
        //    sw[rightBottomRollover_sw] = false; // E-15
        //if (step == 31)
        //    sw[rightBottomRollover_sw] = true; // E-15
        //if (step == 33)
        //    sw[rightBottomRollover_sw] = false; // E-15



        if (step == 20)
        {
            //sw[sStandup_sw] = true;          // D-2
        }
        if (step == 22)
        {
            //sw[sStandup_sw] = false;          // D-2
        }

        
        // Load previous assigned state
        for (int i=0; i < unitsSize; ++i)
        {
            units[i].Assign(unitsA[i]);
			unitsA[i].AssignEos(units[i]); // Update the eos
		}

        for (int i = 0; i < reSize; ++i)
        {
            re[i].Assign(reAs[i]);
		}
		for (int i = 0; i < solenoidsSize; ++i)
		{
			priorSol[i].Assign(sol[i]);
		}


            // Section 2
            // Alternator Unit Logic
    //        if (re[c5] && !c5_re_last)
    //        {
    //            alternatorUnit = alternatorUnit == 0 ? 1 : 0;
				//if (settle == 0) altUnit_eos = true;
    //            
    //        }
    //        if (settle == 0 && altUnit_eos) altUnit_eos = false;


        // Topic: 25 Cent Logic
        bool r_br = units[scoreMotor] != 6;
        bool r_y_3 = units[scoreMotor] != 4 && r_br;
        bool br_b = units[scoreMotor] != 3 && r_y_3;
        bool blu_b = units[scoreMotor] != 2 && br_b;
        bool y_b_1 = false;

        switch (c25_adj) {
        case 2:
            y_b_1 = blu_b;
            break;
        case 3:
            y_b_1 = br_b;
            break;
        case 4:
            y_b_1 = r_y_3;
            break;
        case 5:
            y_b_1 = r_br;
            break;
        default:
            y_b_1 = false;
            break;
        }
        bool r_o = !sw[antiCheat_sw] && sw[c25_sw];
        bool g_o = !sw[antiCheat_sw] && !sw[c25_sw]; // used in Section 4
        reAs[reC25] = (re[reC25] && y_b_1) || r_o;

        // Topic: 10 Cent Logic
        bool blu_y = false;
        switch (c10_adj) {
        case 2:
            blu_y = blu_b;
            break;
        case 3:
            blu_y = br_b;
            break;
        default:
            blu_y = false;
            break;
        }
        bool r_b = blu_y && re[reC10];

        bool blu_br = !sw[antiCheat_sw] && sw[c10_sw];
        switch (c10_adj) {
        case 2:
        case 3:
            reAs[reC10] = blu_br || r_b;
            break;
        default:
            reAs[reC10] = false;
            break;
        }

        // Section 3
        // Topic: Coin Relay Logic
        bool w_b = !sw[antiCheat_sw]
            && sw[c5_sw];
        bool g_w_1 = (w_b && (c5_adj == 1));
        g_w_1 = g_w_1 || blu_br && (c10_adj == 1);
        bool r_w = (units[scoreMotor] != 3 && ball_3_5_adj == 3)
            || (units[scoreMotor] != 5 && ball_3_5_adj == 5)
            /* || re[game]*/;
        g_w_1 = g_w_1 || (r_w && re[reCoin]);
        g_w_1 = g_w_1 || (alternatorUnit == 2 && re[reC5]);
        bool w_grey = /*scoreMotor != 0*/units[scoreMotor] == 0
            && (units[ballCount] == 0 || re[reGame]);
        g_w_1 = g_w_1 || w_grey
            && (units[credit] != 0
                && sw[creditButton_sw]);
        bool coin_re = w_b || g_w_1;
        reAs[reCoin] = w_b || g_w_1;

        // Topic: 5 Cent Logic
        reAs[reC5] = (altUnit_eos && re[reC5])
            || (c5_adj == 2 && w_b);

        // Topic: Coin Lockout Solenoid Logic
        sol[solCoinLockout] = (units[credit] == 0) && w_grey;

        // Topic: Reset Relay Logic
        int tmp = units[scoreMotor];
        bool blu_br_1 = re[reBonus] || /*(scoreMotor == 0) */ (units[scoreMotor] != 0);
        blu_br_1 = blu_br_1
            || (units[pt10] != 0 && units[pt100] != 0 && units[pt1000] != 0 && units[pt10000] != 0);
        bool y_blu_2 = blu_br_1 && (!re[reGame] && !re[reLock]);
        bool blu_w_1 = blu_br_1 && re[reReset];
        bool reset_re = y_blu_2 || blu_w_1 || re[reCoin];
        reAs[reReset] = y_blu_2 || blu_w_1 || re[reCoin];

        // Section 4
        // Topic: Lock Relay Logic
        reAs[reLock] = !sw[kickOff_sw]
            && (units[scoreMotor] == 1
                || sw[leftFlipper_sw]
                || re[reC5]
                || re[reLock]);

        // Topic: Score Motor Advance Logic
        //bool r_b_2 = re[coin] && !impulse;
        //bool br_b_1 = leftFlipper_sw && !impulse;
        //scoreMotor += (r_b_2 || br_b_1) ? 1 : 0;
        //scoreMotor = (scoreMotor > 6) ? 0 : scoreMotor;

        if (!impulse)
        {
                // Score Motor Logic
            if (re[reRocketSpecial]
                || re[reSpaceLabSpecial]
                || re[reSkyLab]
                || re[reBonus]
                || re[reReset]
                || units[scoreMotor] != 0
                || re[rePt50]
                || re[reOutHole]
                || (g_o && re[reC10])
                || (g_o && re[reC25]))
            {
                unitsA[scoreMotor]++;
                impulse = true;
            }
        }
        else
        {
            impulse = false;
        }

        // Topic: Knocker Solenoid Logic
        bool o_r = g_o && !re[reC25] && !re[reC10] && !re[reCoin];
        bool b_w = re[reSpaceLabSpecial] && units[scoreMotor] == 5
            || re[reRocketSpecial] && units[scoreMotor] == 1
            || units[credit].eos()
            || units[ballCount].eos();
        sol[solKnocker] = o_r && b_w;

        //Section 5
        // Topic: Score Drum Units Logic
        if (re[rePt10] || (re[reScoreReset] && units[pt10] != 0))
        {
            unitsA[pt10]++;
        }

        if (re[rePt100] || (re[reScoreReset] && units[pt100] != 0))
        {
            unitsA[pt100]++;
        }

        if (re[rePt1000] || (re[reScoreReset] && units[pt1000] != 0))
        {
            unitsA[pt1000]++;
        }

        bool b_o_1 = (re[reScoreReset] && units[pt10000] != 0);
        if (b_o_1 || units[pt1000] == 9000)
        {
            unitsA[pt10000]++;
        }

        // Topic: Game Relay Logic
        bool game_re_trip = re[reBallIndex] && !re[reGame];
        bool r_g_1 = re[reCoin];                       // Continued in Section 6
        bool r_blu = r_g_1 && units[ballCount] == 0;
        bool game_re_latch = r_blu && units[scoreMotor] == 0;
        if (game_re_trip)
            reAs[reGame] = false;
            //reAs[game] = true;
        else if (game_re_latch)
            reAs[reGame] = true;
            //reAs[game] = false;
        sol[solTotalPaymeter] = game_re_latch;
        if (game_re_latch) 
            unitsA[credit]--;


        // Section 6
        // Topic: Game Over Relay Logic
        bool blu_y_1 = re[reOutHole] && re[reBallIndex] && units[scoreMotor] == 0;
        bool gameOver_re_latch = r_g_1 || (units[ballCount] > 1) && blu_y_1;
        bool grey_g = re[reOutHole];
        bool g_b_3 = grey_g && re[reBallIndex];
        bool b_y_1 = g_b_3
            && units[scoreMotor] == 1
            && (units[ballCount] == 0 || units[ballCount] == 1);
        bool blu_r_1 = !re[reGameOver] && (!re[reLock] || sw[tilt_sw]);
        bool gameOver_re_trip = blu_r_1 || b_y_1;
        if (gameOver_re_trip)
            reAs[reGameOver] = false;
        else if (gameOver_re_latch)
            reAs[reGameOver] = true;

        // Topic: Ball Count Unit Logic
        bool o_r_1 = g_b_3 && units[scoreMotor] == 2;
        bool b_w_4 = r_g_1 && impulse;
        bool grey_b = b_w_4 && !re[reGame];
        o_r_1 = o_r_1 || (b_w_4 && re[reGame]);
        // Decrement Ball Count Unit
        if (o_r_1)
            unitsA[ballCount]--;
		// Increment Ball Count Unit
        if (grey_b)
            unitsA[ballCount]++;

        // Section 7
        // Topic: Ball Release Solenoid
        if (!re[reReset] && !re[reGameOver]) // RED Wire
        {
            sol[solBallRelease] = grey_g && units[scoreMotor] == 4;
        }

        // Topic: Score Reset Relay
        bool grey_w_3 = impulse;
        reAs[reScoreReset] = grey_w_3 && re[reReset];

        // Topic: Credit Unit
        bool grey = grey_w_3 && (re[reC10] || re[reC25]);
        if (grey && !units[credit].eos())
        {
            unitsA[credit]++;
        }

        // Section 8
        // Topic: Spacelab & Rocket Special adjustments
        // TODO: This logic needs to be located in a prior section to properly affect the ball/credit count
        bool br_3 = !re[reOutHole];
        bool grey_o_1 = br_3 && re[reSpaceLabSpecial] && units[scoreMotor] == 5;
        bool br_g_2 = br_3 && re[reRocketSpecial] && units[scoreMotor] == 1;
        grey = grey // Credit Unit Increment
            || (spacelabRocketSpecial_adj == 1 && grey_o_1);
        grey_b = grey_b // Ball Count Unit Increment
            || (spacelabRocketSpecial_adj == 1 && br_g_2)
            || (spacelabRocketSpecial_adj == 2 && grey_o_1)
            || (spacelabRocketSpecial_adj == 2 && br_g_2);
        b_o_1 = b_o_1 // Novelty 
            || (spacelabRocketSpecial_adj == 3 && grey_o_1)
            || (spacelabRocketSpecial_adj == 3 && br_g_2);
        // Match Adjustment
        bool r_b_5 = units[ballCount] == 1;
        bool r_b_4 = r_b_5 && re[reBallIndex] && re[reOutHole] && units[scoreMotor] == 0;
        bool blu_o_2 = r_b_4 && units[pt10] == units[noMatch] && match_adj;

        // High Score Unit Logic
        // TODO: High Score Unit Logic needs to be implemented

        // Section 9
        // Topic: Double Bonus Relay Logic
        bool r_g_5 = re[reDoubleBonus] || (r_b_5 && !re[reBallIndex]);
        reAs[reDoubleBonus] = r_g_5;

        // Topic: Advance Unit Stepper Logic (Reset)
        bool r_blu_2 = (r_y_3 && units[scoreMotor] == 3 && !re[reDoubleBonus])
			|| units[scoreMotor] == 5; // Was 6, 5 and 6 are the same position
        if (r_blu_2 && re[reBonus])
			unitsA[advanceCount].reset();

        // Topic: Bonus Relay
        bool grey_blu = units[advanceCount] != 0 
            && (re[reReset] || re[reBonus]);
        bool w_blu_1 = units[scoreMotor] == 0;
        bool g_w_2 = w_blu_1 && units[ballCount] != 0;
        reAs[reBonus] = grey_blu 
            || (g_w_2 && units[advanceCount] != 0 && sw[outHole_sw]);
        if (!re[reReset]) // BLUE - Yellow - White Wire
        {

            // Topic: Outhole Relay
            bool blu_y_4 = g_w_2 
                && units[advanceCount] == 0 
                && !re[reBonus];
            reAs[reOutHole] = (units[scoreMotor] != 5 && re[reOutHole]) 
                || blu_y_4;

            // Topic: Ball Index Relay
            bool o = w_blu_1 && re[reGameOver] && re[reOutHole];
            o = o || ((units[advanceCount] == 1
                || units[advanceCount] == 2
                || units[advanceCount] == 3)
                &&
                (re[rePt10] || re[rePt100] || re[rePt1000]));
            bool w_r_1 = !re[reOutHole] || units[scoreMotor] != 3;
            reAs[reBallIndex] = o || (w_r_1 && re[reBallIndex]);

            // Section 10
            // Topic: 5 Ball Inline Relay Logic
            reAs[reFiveBallInline] = w_r_1 && (re[reRocketSpecial] || re[reSpaceLabSpecial]);

            // Topic: 100000 Point Relay Logic
            reAs[rePt100000] = re[rePt100000] || (units[pt10000] == 9 && units[pt1000] == 9);
        }

        if (!re[reReset] && !re[reGameOver]) // RED Wire
        {
            // Topic: Change Relay Logic
            reAs[reChange] = units[noMatch] % 2 == 1;

            // Topic: The S-K-Y-L-A-B are locking relays and release
            // when Skylab solenoid is activated.
            // S Relay Logic
            reAs[reS] = sw[sStandup_sw] && !re[reS]
                || re[reS] && !re[reSkylabBankReset];

            // Section 11
            // K Relay Logic
            reAs[reK] = sw[kStandup_sw] && !re[reK]
                || re[reK] && !re[reSkylabBankReset];

            // Y Relay Logic
            reAs[reY] = sw[yStandup_sw] && !re[reY]
                || re[reY] && !re[reSkylabBankReset];

            // L Relay Logic
            reAs[reL] = sw[lStandup_sw] && !re[reL]
                || re[reL] && !re[reSkylabBankReset];

            // A Relay Logic
            reAs[reA] = sw[aStandup_sw] && !re[reA]
                || re[reA] && !re[reSkylabBankReset];

            // B Relay Logic
            reAs[reB] = sw[bStandup_sw] && !re[reB]
                || re[reB] && !re[reSkylabBankReset];

            // Topic: 50 Point Relay Logic
            bool br_b_1 = sw[kStandup_sw] && re[reK];
            br_b_1 = br_b_1 || (sw[yStandup_sw] && re[reY]);
            br_b_1 = br_b_1 || (sw[aStandup_sw] && re[reA]);
            br_b_1 = br_b_1 || sw[bStandup_sw] && re[reB];
            bool br_1 = units[scoreMotor] != 5;
            reAs[rePt50] = (br_1 && re[rePt50]) || br_b_1;

            // section 12
            // Topic: Rocket Special Relay Logic
            bool y_0 = !sw[left1CaptiveBall_sw]
                && sw[right3CaptiveBall_sw]
                && sw[right4CaptiveBall_sw];
            bool y_g = !sw[right1CaptiveBall_sw]
                && sw[left3CaptiveBall_sw]
                && sw[left4CaptiveBall_sw];
            bool g_r_1 = (re[reCaptiveBall] && y_0) || (!re[reCaptiveBall] && y_g);
            reAs[reRocketSpecial] = (g_r_1 && re[reFiveBallInline])
                || (br_1 && re[reRocketSpecial]);

            // Topic: SkyLab Relay Logic
            bool g_y = br_1 && re[reSkyLab];
            reAs[reSkyLab] = g_y ||
                (   units[scoreMotor] == 0
                    && re[reS] 
                    && re[reK] 
                    && re[reY] 
                    && re[reL] 
                    && re[reA] 
                    && re[reB]);

			// Captive Ball Relay Logic
            // Back to BLACK wire see below ****

            // Section 13
			// Topic: SpaceLab Relay Logic
            bool w_grey_2 =
                (spaceLab_adj == Liberal && units[advanceCount] == 5
                || spaceLab_adj == Conservitive && units[advanceCount] == 7)
                && units[advanceCount].eos();
            reAs[reSpaceLab] = w_grey_2 
				|| (units[scoreMotor] != 4 || !re[reSpaceLabSpecial])
                && re[reSpaceLab];

			// Topic: SpaceLab Special Relay Logic
			bool g_1 = r_br && re[reSpaceLabSpecial];
            bool b_r = (sw[leftBotOutsideRollover_sw] && !re[reChange])
                || (sw[rightBotOutsideRollover_sw] && re[reChange]);
            bool br_y = (sw[leftBotOutsideRollover_sw] && re[reChange])
				|| (sw[rightBotOutsideRollover_sw] && !re[reChange]);
            reAs[reSpaceLabSpecial] = (b_r && re[reSpaceLab])
                || g_1;
            br_y = br_y || (b_r && !re[reSpaceLab]);

			// Topic: 10 Point Relay Logic
            bool g_b = sw[sStandup_sw] && re[reS];
            g_b = g_b || (sw[lStandup_sw] && re[reL]);
            g_b = g_b || !units[pt10].eos() && re[rePt10];
			g_b = g_b || sw[leftKickerCount_sw] || sw[rightKickerCount_sw];
			g_b = g_b || (units[scoreMotor] == 5 || impulse) && re[rePt50]; // Was 6, 5 and 6 are the same position
            reAs[rePt10] = g_b;

            // Section 14
			// Topic: 1000 Point Relay Logic
			br_y = br_y || (units[scoreMotor] == 5 || impulse) && re[reBonus]; // Was 6, 5 and 6 are the same position
            br_y = br_y || br_3 && units[advanceCount].eos();
            br_y = br_y || !units[pt1000].eos() && re[rePt1000];
			bool o_b_3 = (sw[right4CaptiveBall_sw] && !re[reCaptiveBall])
                || (sw[left4CaptiveBall_sw] && re[reCaptiveBall]);
            reAs[rePt1000] = br_y 
                || (o_b_3 && re[reFiveBallInline])
                || (o_b_3 && !re[reFiveBallInline] && re[reSpaceLab]);

			// Topic: 100 Point Relay Logic
            bool w_r = o_b_3 && !re[reFiveBallInline] && !re[reSpaceLab];
			w_r = w_r || sw[rightJetBumper_sw] || sw[leftJetBumper_sw];
            w_r = w_r || units[noMatch].eos();
            w_r = w_r || units[pt10] == 9 && re[rePt10];
			w_r = w_r || !units[pt100].eos() && re[rePt100];
            bool g_4 = sw[leftTopRollover_sw] || sw[rightBottomRollover_sw];
			bool grey_w = sw[rightTopRollover_sw] || sw[leftBottomRollover_sw];
			w_r = w_r || g_4 && re[reChange] || grey_w && !re[reChange];
			reAs[rePt100] = w_r;

            // Section 15
			// Topic: Advance Unit Stepper Logic (Count)
            bool grey_y_1 = grey_g && units[scoreMotor] == 3;
            grey_y_1 = grey_y_1 
                || (units[scoreMotor] == 3 || units[scoreMotor] == 4) 
                && re[reSkyLab];
            grey_y_1 = grey_y_1 
                || g_4 && !re[reChange] 
                || grey_w && re[reChange];
            if (grey_y_1)
            {
                unitsA[advanceCount]++;
            }

            // Topic: No Match Unit Stepper Logic
            if (sw[leftRolloverButton_sw] || sw[rightRolloverButton_sw])
            {
                unitsA[noMatch]++;
			}


        }

        // Section 12
        // Back to BLACK wire
        // Topic: Captive Ball Relay Logic
        bool b_blu = units[scoreMotor] != 0
            && (re[reCoin]
                || re[reGameOver]
                || re[reRocketSpecial]);
        bool captiveBall_re_latch = b_blu && sw[left2CaptiveBall_sw];
        bool captiveBall_re_trip = b_blu && sw[right2CaptiveBall_sw];
        if (captiveBall_re_trip)
            reAs[reCaptiveBall] = false;
        else if (captiveBall_re_latch)
            reAs[reCaptiveBall] = true;

        // Section 1
        reAs[reSkylabBankReset] =
            (re[reCoin] || re[reSkyLab]) 
            && units[scoreMotor] == 2;


   //     if (step == 4 || step == 13 || step == 20 || step == 21 || step == 26)
   //     {
   //         std::cout << "<<<<< Current Values" << "\n";
   //         for (int i=0; i < reSize; ++i)
   //         {
   //             std::string out = reAs[i].Print(true);
   //             if (out != "")
   //                 std::cout << out << "\n";
			//}

   //         for (int i = 0; i < unitsSize; ++i)
   //         {
   //             std::string out = unitsA[i].PrintNot(0);
   //             if (out != "")
   //                 std::cout << out << "\n";
			//}
   //         std::cout << ">>>>>" << "\n";
   //     }


        for (int i = 0; i < swSize; ++i)
        {
            std::string out = sw[i].Print(priorSw[i], true);
            if (out != "")
                std::cout << out << "\n";
        }

        for (int i=0; i < reSize; ++i)
        {
            std::string out = reAs[i].Print(re[i], true);
            if (out != "")
                std::cout << out << "\n";
        }

        for (int i = 0; i < unitsSize; ++i)
        {
            std::string out = unitsA[i].Print(units[i], true);
            if (out != "")
                std::cout << out << "\n";
            out = unitsA[i].PrintEos(units[i], true);
            if (out != "")
                std::cout << out << "\n";
		}

        for (int i = 0; i < solenoidsSize; ++i)
        {
            std::string out = sol[i].Print(priorSol[i], true);
            if (out != "")
                std::cout << out << "\n";
        }


    }




}


