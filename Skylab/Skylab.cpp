// Skylab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>

int main()
{

	// TODO: Fix Impulse Logic
	// TODO: Fix Score Motor Logic
	// TODO: Fox EOS Logic
    

    enum strictness {Liberal, Conservitive};

    // Adjustments
    int c25_adj = 5;
    int c10_adj = 1;
    int c5_adj = 2;
    int ball_3_5_adj = 5;
	int spacelabRocketSpecial_adj = 1;
	bool match_adj = false;
	strictness spaceLab_adj = Conservitive;



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
    bool spaceLab_re = false;    // E-13
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
	bool advanceCountUnit_eos = 8;      // E-13

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
	bool noMatchUnit_eos = false;        // E-14

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
    bool pt10DrumUnit_sol_eos = false;      // E-13
    bool pt100DrumUnit_sol_eos = false;     // E-14
    bool pt1000DrumUnit_sol_eos = false;    // E-14
    bool pt10000DrumUnit_sol_eos = false;   // E-14


    // Switches
    bool tilt_sw = false;
    bool kickOff_sw = false;
    bool leftFlipper_sw = false; // C-16 (2)
    bool c25_sw = false;          // D-2
    bool c10_sw = false;          // D-2
    bool c5_sw = false;           // D-3
    bool antiCheat_sw = false;    // C-2
    bool creditButton_sw = false; // E-3
	bool sStandup_sw = false;     // E-10
    bool kStandup_sw = false;     // E-11
    bool yStandup_sw = false;     // E-11
    bool lStandup_sw = false;     // E-11
    bool aStandup_sw = false;     // E-11
    bool bStandup_sw = false;     // E-11
	bool right1CaptiveBall_sw = false; // D-12
	bool left1CaptiveBall_sw = false;  // D-12
    bool right2CaptiveBall_sw = false; // D-12
    bool left2CaptiveBall_sw = false;  // D-12
    bool right3CaptiveBall_sw = false; // D-12
    bool left3CaptiveBall_sw = false;  // D-12
    bool right4CaptiveBall_sw = false; // D-12
    bool left34aptiveBall_sw = false;  // D-12
	bool leftBotOutsideRollover_sw = false; // D-13
    bool rightBotOutsideRollover_sw = false; // D-13
	bool leftKickerCount_sw = false; // D-13
	bool rightKickerCount_sw = false; // D-13
    bool leftJetBumper_sw = false; // E-14
	bool rightJetBumper_sw = false; // E-14
    bool rightTopRollover_sw = false; // E-15
    bool leftTopRollover_sw = false;  // E-15
    bool rightBottomRollover_sw = false; // E-15
	bool leftBottomRollover_sw = false;  // E-15

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

        // Simulate time for relays to settle
        for (int settle = 0; settle < 3; ++settle)
        {
            std::cout << "----- settle = " << settle << "\n";

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

            grey_b = b_w_4 && !game_re;
            ballCountUnit += grey_b ? 1 : 0;
            std::cout << "ballCountResetUnit = " << ballCountResetUnit << "\n";
            std::cout << "ballCountUnit = " << ballCountUnit << "\n";

            // Section 7
            // Ball Release Solenoid
            if (!reset_re && !gameOver_re) // RED Wire
            {
                ballRelease_sol = grey_g && scoreMotor == 4;
            }
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
            if (!reset_re) // BLUE - Yellow - White Wire
            {

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

                // Section 10
                // 5 Ball Inline Relay Logic
                fiveBallInline_re = w_r_1 && (rocketSpecial_re || spaceLabSpecial_re);
                std::cout << "fiveBallInline_re = " << fiveBallInline_re << "\n";

                // 100000 Point Relay Logic
                pt100000_re = pt100000_re || (pt10000 == 9 && pt1000 == 9);
                std::cout << "pt100000_re = " << pt100000_re << "\n";
            }

            if (!reset_re && !gameOver_re) // RED Wire
            {
                // Change Relay Logic
                change_re = noMatchUnit % 2 == 1;
                std::cout << "change_re = " << change_re << "\n";

                // S Relay Logic
                s_re = sStandup_sw && !s_re;
                bool g_b = kStandup_sw && k_re;
                std::cout << "s_re = " << s_re << "\n";

                // Section 11
                // K Relay Logic
                k_re = kStandup_sw && !k_re;
                bool br_b_1 = yStandup_sw && y_re;
                std::cout << "k_re = " << k_re << "\n";

                // Y Relay Logic
                y_re = yStandup_sw && !y_re;
                br_b_1 = br_b_1 || (lStandup_sw && l_re);
                std::cout << "y_re = " << y_re << "\n";

                // L Relay Logic
                l_re = lStandup_sw && !l_re;
                g_b = g_b || (aStandup_sw && a_re);
                std::cout << "l_re = " << l_re << "\n";

                // A Relay Logic
                a_re = aStandup_sw && !a_re;
                br_b_1 = br_b_1 || (bStandup_sw && b_re);
                std::cout << "a_re = " << a_re << "\n";

                // B Relay Logic
                b_re = bStandup_sw && !b_re;
                br_b_1 = br_b_1 || bStandup_sw && b_re;
                std::cout << "b_re = " << b_re << "\n";

                // 50 Point Relay Logic
                bool br_1 = scoreMotor != 5;
                pt50_re = (br_1 && pt50_re) || br_b_1;

                // section 12
                // Rocket Special Relay Logic
                bool y_0 = !left1CaptiveBall_sw
                    && right3CaptiveBall_sw
                    && right4CaptiveBall_sw;
                bool y_g = !right1CaptiveBall_sw
                    && left3CaptiveBall_sw
                    && left34aptiveBall_sw;
                bool g_r_1 = (captiveBall_re && y_0) || (!captiveBall_re && y_g);
                rocketSpecial_re = (g_r_1 && fiveBallInline_re)
                    || (br_1 && rocketSpecial_re);
                std::cout << "rocketSpecial_re = " << rocketSpecial_re << "\n";

                // SkyLab Relay Logic
                bool g_y = br_1 && skyLab_re;
                skyLab_re = g_y ||
                    (scoreMotor == 1 && s_re && k_re && y_re && l_re && a_re && b_re);
                std::cout << "skyLab_re = " << skyLab_re << "\n";
   //         }
   //         // Back to BLACK wire
			//// Captive Ball Relay Logic
   //         bool b_blu = scoreMotor != 0
   //             && (coin_re
   //                 || gameOver_re
   //                 || rocketSpecial_re);
   //         captiveBall_re_latch = b_blu && left2CaptiveBall_sw;
			//captiveBall_re_trip = b_blu && right2CaptiveBall_sw;
   //         if (captiveBall_re_trip)
   //             captiveBall_re = false;
   //         else if (captiveBall_re_latch)
			//	captiveBall_re = true;
   //         std::cout << "captiveBall_re_latch = " << captiveBall_re_latch << "\n";
   //         std::cout << "captiveBall_re_trip = " << captiveBall_re_trip << "\n";
			//std::cout << "captiveBall_re = " << captiveBall_re << "\n";

   //         if (!reset_re && !gameOver_re) // RED Wire
   //         {
                // Section 13
				// SpaceLab Relay Logic
                bool w_grey_2 =
                    (spacelabRocketSpecial_adj == Liberal && advanceCountUnit == 5)
                    && (spacelabRocketSpecial_adj == Conservitive && advanceCountUnit == 7)
                    && advanceCountUnit == advanceCountUnit_eos;
                spaceLab_re = w_grey_2 
					|| (scoreMotor != 4 || !spaceLabSpecial_re)
                    && spaceLab_re;
				std::cout << "spaceLab_re = " << spaceLab_re << "\n";

				// SpaceLab Special Relay Logic
				bool g_1 = r_br && spaceLabSpecial_re;
                bool b_r = (leftBotOutsideRollover_sw && !change_re)
                    || (rightBotOutsideRollover_sw && change_re);
                bool br_y = (leftBotOutsideRollover_sw && change_re)
					|| (rightBotOutsideRollover_sw && !change_re);
                spaceLabSpecial_re = (b_r && spaceLab_re)
                    || g_1;
                br_y = br_y || (b_r && !spaceLab_re);

				// 10 Point Relay Logic
				g_b = g_b || pt10DrumUnit_sol_eos && pt10_re;
				g_b = g_b || leftKickerCount_sw || rightKickerCount_sw;
                g_b = g_b || (scoreMotor == 6 || impulse) || pt50_re;
                pt10_re = g_b;
				std::cout << "pt10_re = " << pt10_re << "\n";

                // Section 14
				// 1000 Point Relay Logic
                br_y = br_y || (scoreMotor == 6 || impulse) && bonus_re;
                br_y = br_y || br_3 && advanceCountUnit_eos;
                br_y = br_y || pt1000DrumUnit_sol_eos && pt1000_re;
				bool o_b_3 = (right4CaptiveBall_sw && !captiveBall_re)
                    || (left4aptiveBall_sw && captiveBall_re);
                pt1000_re = br_y 
                    || (o_b_3 && fiveBallInline_re)
                    || (o_b_3 && !fiveBallInline_re && spaceLab_re);
				std::cout << "pt10_re = " << pt10_re << "\n";

				// 100 Point Relay Logic
                bool w_r = o_b_3 && !fiveBallInline_re && !spaceLab_re;
				w_r = w_r || rightJetBumper_sw || leftJetBumper_sw;
                w_r = w_r || noMatchUnit_eos;
                w_r = w_r || pt10DrumUnit_sol == 9 && pt10_re;
				w_r = w_r || !pt100DrumUnit_sol_eos && pt100_re;
                bool g_4 = leftTopRollover_sw || rightBottomRollover_sw;
				bool grey_w = rightTopRollover_sw || leftBottomRollover_sw;
				w_r = w_r || g_4 && change_re || grey_w && !change_re;
				pt100_re = w_r;
				std::cout << "pt10_re = " << pt10_re << "\n";

                // Section 15
				// Advance Unit Stepper Logic (Count)
                bool grey_y_1 = grey_g && scoreMotor == 3;
                grey_y_1 = grey_y_1 
                    || (scoreMotor == 3 
                    || scoreMotor == 4) && skyLab_re;
                grey_y_1 = grey_y_1 || g_4 && change_re || grey_w && !change_re;
				advanceCountUnit += grey_y_1 ? 1 : 0;
				std::cout << "spaceLabSpecial_re = " << spaceLabSpecial_re << "\n";




            }

            // Section 12
            // Back to BLACK wire
            // Captive Ball Relay Logic
            bool b_blu = scoreMotor != 0
                && (coin_re
                    || gameOver_re
                    || rocketSpecial_re);
            captiveBall_re_latch = b_blu && left2CaptiveBall_sw;
            captiveBall_re_trip = b_blu && right2CaptiveBall_sw;
            if (captiveBall_re_trip)
                captiveBall_re = false;
            else if (captiveBall_re_latch)
                captiveBall_re = true;
            std::cout << "captiveBall_re_latch = " << captiveBall_re_latch << "\n";
            std::cout << "captiveBall_re_trip = " << captiveBall_re_trip << "\n";
            std::cout << "captiveBall_re = " << captiveBall_re << "\n";

        }
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
