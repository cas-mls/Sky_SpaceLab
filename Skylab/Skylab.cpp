// Skylab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{

    // Adjustments
    int c25_adj = 5;
    int c10_adj = 1;
    int c5_adj = 2;
    int ball_3_5_adj = 5;
	int spacelabRocketSpecial_adj = 1;
	bool match_adj = false;

    // Relays
    bool a_re = false;          // E-11
    bool b_re = false;          // E-11
    bool ballIndex_re = false;  // E-9
    bool bonus_re = false;      // E-9
    bool captiveBall_re_latch = false;  //E-12
    bool captiveBall_re_trip = false;   //E-12
    bool captiveBall_re = false;        // Latched Lalue
    bool change_re = false;     // E10
    bool coin_re = false;       //E-3
    bool doubleBonus_re = false;// E-9
    bool fiveBallInline_re = false;     // E-10
    bool c5_re = false;         // E-3
    bool c10_re = false;        // E-2
    bool c25_re = false;        // E-2
    bool pt50_re = false;
    bool gameOver_re_latch = false;     // E-6
    bool gameOver_re_trip = true;       // E-6
    bool gameOver_re = false;           // Latched Lalue
    bool game_re_latch = false; // E-5
    bool game_re_trip = true;   // E-5
    bool game_re = false;               // Latched Lalue
    bool pt100000_re = false;   // E-10
    bool k_re = false;          // E-11
    bool l_re = false;          // E-11
    bool lock_re = false;       // E-4
    bool outHole_re = false;    // E-9
    bool reset_re = false;      // E-3
    bool rocketSpecial_re = false;      //E-12
    bool s_re = false;          // E-10
    bool scoreReset_re = false; // E-7
    bool skyLab_re = false;     // E-12
    bool spaceLabSpecial_re = false;    // E-13
    bool pt10_re = false;       //E-13
    bool pt100_re = false;      //E-14
    bool pt1000_re = false;     //E-14
    bool y_re = false;          // E-11

    // Score Motor
    int scoreMotor = 0;         // E-4
    bool impulse = false;

    // Advance Unit Stepper
    int advanceCountUnit = 0;           // E-9
    bool advanceResetUnit = false;      // E-15

    // Alternator Unit
    int alternatorUnit = 0;             // E-2
    const int altUnit_eos = 0;          // TODO: altUnit_eos - Don't know what value;

    // Ball Count Unit Stepper
    int ballCountUnit = 0;              // E-6
    bool ballCountResetUnit = false;    // E-6
    const int ballCount_eos = 10;

    // No Match Unit Stepper
    int noMatchUnit = 0;                // E-15
    bool noMatchResetUnit = false;      // E-15

    // Credit Unit Stepper
    int creditUnit = 0;                 // E-7
    bool creditResetUnit = false;       // E-6
    int creditUnit_eos = 10;            // TODO: creditUnit_eos - Don't know what value;

    // SkyLab Unit Stepper
    int skyLabUnit = 0;                // ???
    bool skyLabResetUnit = false;      // D-1

    // Solenoids
    bool ballRelease_sol = false;       // E-7
    bool coinLockout_sol = false;       // E-3
    bool knocker_sol = false;           // D-4
    bool leftFlipper_sol = false;       // E-16
    bool leftJetBumper_sol = false;     // E-16
    bool largeChime_sol = false;        // E-15
    bool mediumChime_sol = false;       // E-15
    bool SmallChime_sol = false;        // E-15
    bool pt10DrumUnit_sol = false;      // E-5
    bool pt100DrumUnit_sol = false;     // E-5
    bool pt1000DrumUnit_sol = false;    // E-5
    bool pt10000DrumUnit_sol = false;   // E-5
    bool totalPaymeter_sol = false;     // E-5
    int pt10 = 0;
    int pt100 = 0;
    int pt1000 = 0;
    int pt10000 = 0;

    // Switches
    bool tilt_sw = false;
    bool kickOff_sw = false;
    bool leftFlipper_sw = false; // C-16 (2)
    bool c25_sw = false;          // D-2
    bool c10_sw = false;          // D-2
    bool c5_sw = false;           // D-3
    bool antiCheat_sw = false;    // C-2
    bool creditButton_sw = false; // E-3

    // Odd Items
	bool c5_re_last = false;

	for (int step = 0; step < 10; ++step)
    {
        std::cout << "***** step = " << step << "\n";

        if (step == 1)
            leftFlipper_sw = true;          // E-4
        if (step == 2)
        {
            leftFlipper_sw = false;          // E-4
            c10_sw = true;          // D-2
        }
        if (step == 3)
            c10_sw = false;          // D-2
        if (step == 4)
            creditButton_sw = true;
        if (step == 5)
            creditButton_sw = false;
        std::cout << "leftFlipper_sw = " << leftFlipper_sw << "\n";
        std::cout << "c10_sw = " << c10_sw << "\n";
        std::cout << "creditButton_sw = " << creditButton_sw << "\n";

        // Section 2

        // Alternator Unit Logic
        if (c5_re && !c5_re_last)
        {
            alternatorUnit = alternatorUnit == 0 ? 1 : 0;
        }
        c5_re_last = c5_re;
        std::cout << "alternatorUnit = " << alternatorUnit << "\n";

        // 25 Cent Logic
        bool r_br = scoreMotor != 6;
        bool r_y_3 = scoreMotor != 4 && r_br;
        bool br_b = scoreMotor != 3 && r_y_3;
        bool blu_b = scoreMotor != 2 && br_b;
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
        bool r_o = !antiCheat_sw && c25_sw;
        bool g_o = !antiCheat_sw && !c25_sw; // used in Section 4
        c25_re = (c25_re && y_b_1) || r_o;
        std::cout << "c25_re = " << c25_re << "\n";

        // 10 Cent Logic
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
        bool r_b = blu_y && c10_re;

        bool blu_br = !antiCheat_sw && c10_sw;
        switch (c10_adj) {
        case 2:
        case 3:
            c10_re = blu_br || r_b;
            break;
        default:
            c10_re = false;
            break;
        }
        std::cout << "c10_re = " << c10_re << "\n";

        // Section 3
        // Coin Relay Logic
        bool w_b = !antiCheat_sw
            && c5_sw;
        bool g_w_1 = (w_b && (c5_adj == 1));
        g_w_1 = g_w_1 || blu_br && (c10_adj == 1);
        bool r_w = (scoreMotor != 3 && ball_3_5_adj == 3)
            || (scoreMotor != 5 && ball_3_5_adj == 5)
            || game_re;
        g_w_1 = g_w_1 || (r_w && coin_re);
        g_w_1 = g_w_1 || (alternatorUnit == 2 && c5_re);
        bool w_grey = /*scoreMotor != 0*/scoreMotor == 0
            && (ballCountUnit == 0 || game_re);
        g_w_1 = g_w_1
            || (creditUnit == 0
                && creditButton_sw);
        coin_re = w_b || g_w_1;
        std::cout << "coin_re = " << coin_re << "\n";

        // 5 Cent Logic
        c5_re = ((alternatorUnit == altUnit_eos) && c5_re)
            || (c5_adj == 2 && w_b);
        std::cout << "c5_re = " << c5_re << "\n";

        // Coin Lockout Solenoid Logic
        coinLockout_sol = (creditUnit != 0) && !w_grey;
        std::cout << "coinLockout_sol = " << coinLockout_sol << "\n";

        // Reset Relay Logic
        bool blu_br_1 = bonus_re || /*(scoreMotor == 0) */ (scoreMotor != 0);
        blu_br_1 = blu_br_1
            || (pt10 == 0 && pt100 == 0 && pt1000 == 0 && pt10000 == 0);
        bool y_blu_2 = blu_br_1 && (!game_re && !lock_re);
        bool blu_w_1 = blu_br_1 && reset_re;
        reset_re = y_blu_2 || blu_w_1 || coin_re;
        std::cout << "reset_re = " << reset_re << "\n";

        // Section 4
        // Lock Relay Logic
        lock_re = !kickOff_sw
            && (scoreMotor == 1
                || leftFlipper_sw
                || c5_re
                || lock_re);
        std::cout << "lock_re = " << lock_re << "\n";

        // Score Motor Logic
        if (rocketSpecial_re
            || spaceLabSpecial_re
            || skyLab_re
            || bonus_re
            || reset_re
            || scoreMotor != 0
            || pt50_re
            || outHole_re
            || (g_o && c10_re)
            || (g_o && c25_re))
        {
            scoreMotor += 1;
            impulse = true;
        }
        else
        {
            impulse = false;
        }
        std::cout << "scoreMotor = " << scoreMotor << "\n";
        std::cout << "impulse = " << impulse << "\n";

        //Knocker Solenoid Logic
        bool o_r = g_o && !c25_re && !c10_re && coin_re;
        bool b_w = spaceLabSpecial_re && scoreMotor == 5
            || rocketSpecial_re && scoreMotor == 1
            || creditUnit == creditUnit_eos
            || ballCountUnit == ballCount_eos;
        knocker_sol = o_r && b_w;
        std::cout << "knocker_sol = " << knocker_sol << "\n";

        //Section 5
        // Score Drum Units Logic
        pt10 += (pt10_re || (scoreReset_re && pt10 != 0)) ? 10 : 0;
        pt100 += (pt100_re || (scoreReset_re && pt100 != 0)) ? 100 : 0;
        pt1000 += (pt1000_re || (scoreReset_re && pt1000 != 0)) ? 1000 : 0;
        bool b_o_1 = (scoreReset_re && pt10000 != 0);
        pt10000 += (pt1000 == 9000 || b_o_1) ? 10000 : 0;
        pt10 = (pt10 >= 100) ? 0 : pt10;
        pt100 = (pt100 >= 1000) ? 0 : pt100;
        pt1000 = (pt1000 >= 10000) ? 0 : pt1000;
        std::cout << "pt10 = " << pt10 << "\n";
        std::cout << "pt100 = " << pt100 << "\n";
        std::cout << "pt1000 = " << pt1000 << "\n";
        std::cout << "pt10000 = " << pt10000 << "\n";


        // Game Relay Logic
        game_re_trip = ballIndex_re && !game_re;
        bool r_g_1 = coin_re;                       // Continued in Section 6
        bool r_blu = r_g_1 && ballCountUnit == 0;
        game_re_latch = r_blu && scoreMotor == 0;
        totalPaymeter_sol = game_re_latch;
        creditResetUnit = game_re_latch;
        if (game_re_trip)
            game_re = false;
        else if (gameOver_re_latch)
            game_re = true;
        std::cout << "game_re_latch = " << game_re_latch << "\n";
        std::cout << "game_re_trip = " << game_re_trip << "\n";
        std::cout << "game_re = " << game_re << "\n";
        std::cout << "totalPaymeter_sol = " << totalPaymeter_sol << "\n";
        std::cout << "creditResetUnit = " << creditResetUnit << "\n";

        // Section 6
        // Game Over Relay Logic
        bool blu_y_1 = outHole_re && ballIndex_re && scoreMotor == 0;
        gameOver_re_latch = r_g_1 || (ballCountUnit > 1) && blu_y_1;
        bool grey_g = outHole_re;
        bool g_b_3 = grey_g && ballIndex_re;
        bool b_y_1 = g_b_3
            && scoreMotor == 1
            && (ballCountUnit == 0 || ballCountUnit == 1);
        bool blu_r_1 = !gameOver_re && (!lock_re || tilt_sw);
        gameOver_re_trip = blu_r_1 || b_y_1;
        if (gameOver_re_trip)
            gameOver_re = false;
        else if (gameOver_re_latch)
            gameOver_re = true;
        std::cout << "gameOver_re_latch = " << gameOver_re_latch << "\n";
        std::cout << "gameOver_re_trip = " << gameOver_re_trip << "\n";
        std::cout << "gameOver_re = " << gameOver_re << "\n";

        // Ball Count Unit Logic
        bool o_r_1 = g_b_3 && scoreMotor == 2;
        bool b_w_4 = g_b_3 && impulse;
        bool grey_b = b_w_4 && !game_re;
		o_r_1 = o_r_1 || (b_w_4 && game_re);
		ballCountResetUnit = o_r_1;
        ballCountUnit = ballCountResetUnit ? 0 : ballCountUnit;

        grey_b = b_w_4 && !game_re ;
        ballCountUnit += grey_b ? 1 : 0;
        std::cout << "ballCountResetUnit = " << ballCountResetUnit << "\n";
		std::cout << "ballCountUnit = " << ballCountUnit << "\n";

        // Section 7
        // Ball Release Solenoid
        ballRelease_sol = grey_g && scoreMotor == 4;
        std::cout << "ballRelease_sol = " << ballRelease_sol << "\n";

        // Score Reset Relay
        bool grey_w_3 = impulse;
        scoreReset_re = grey_w_3 && reset_re;
        std::cout << "scoreReset_re = " << scoreReset_re << "\n";

        // Credit Unit
        bool grey = grey_w_3 && (c10_re || c25_re);
		creditUnit += grey && !creditUnit_eos ? 1 : 0;
        std::cout << "creditUnit = " << creditUnit << "\n";

        // Section 8
		// Spacelab & Rocket Special adjustments
        // TODO: This logic needs to be located in a prior section to properly affect the ball/credit count
        bool br_3 = !outHole_re;
		bool grey_o_1 = br_3 && spaceLabSpecial_re && scoreMotor == 5;
        bool br_g_2 = br_3 && rocketSpecial_re && scoreMotor == 1;
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
        bool r_b_5 = ballCountUnit == 1;
        bool r_b_4 = r_b_5 && ballIndex_re && outHole_re && scoreMotor == 0;
        bool blu_o_2 = r_b_4 && pt10 == noMatchUnit && match_adj;
		// High Score Unit Logic
		// TODO: High Score Unit Logic needs to be implemented

        // Section 9
		// Double Bonus Relay Logic
        bool r_g_5 = doubleBonus_re || (r_b_5 && !ballIndex_re);
		doubleBonus_re = r_g_5;
        std::cout << "doubleBonus_re = " << doubleBonus_re << "\n";

		// Advance Unit Stepper Logic (Reset)
        bool r_blu_2 = (r_y_3 && scoreMotor == 3 && !doubleBonus_re)
            || scoreMotor == 6;
        advanceResetUnit = r_blu_2 && bonus_re;
        std::cout << "advanceResetUnit = " << advanceResetUnit << "\n";

        // Bonus Relay
        bool grey_blu = advanceCountUnit == 0 && (reset_re || bonus_re);
        bool w_blu_1 = scoreMotor == 0;
        bool g_w_2 = w_blu_1 && ballCountUnit == 0;
        bonus_re = (g_w_2 && advanceCountUnit == 0 && outHole_re) || grey_blu;
        std::cout << "bonus_re = " << bonus_re << "\n";

        // Outhole Relay
        bool blu_y_4 = advanceCountUnit != 0 && bonus_re;
        outHole_re = (scoreMotor == 5 && outHole_re) || blu_y_4;
        std::cout << "outHole_re = " << outHole_re << "\n";

        // Ball Index Relay
        bool o = w_blu_1 && gameOver_re && outHole_re;
        o = o || ((advanceCountUnit == 1
                || advanceCountUnit == 2
                || advanceCountUnit == 3)
            &&
            (pt10_re || pt100_re || pt1000_re));
        bool w_r_1 = !outHole_re || scoreMotor == 3;
        ballIndex_re = o || (w_r_1 && ballIndex_re);
        std::cout << "ballIndex_re = " << ballIndex_re << "\n";







    }




    //ballCountResetUnit = g_b_3 && scoreMotor == 2;
	//ballCountUnit = b_w_4 || game_re ? 0 : ballCountUnit;
 //   bool grey_b = b_w_4 && !game_re;
	//ballCountUnit += grey_b ? 1 : 0;



    
    //gameOver_re_trip = blu_r_1 || blu_y_1; // This is latched logic

    //lock_re = !kickOff_sw || scoreMotor == 1 || leftFlipper_sw || lock_re;

    //bool b_w_4 = coin_re && impulse;
    //ballCountResetUnit = g_b_3 && scoreMotor == 2 || (b_w_4 && game_re);








    // Section 4 Latched Logic

    std::cout << "Hello World!\n";
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
