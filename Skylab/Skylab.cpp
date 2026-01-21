// Skylab.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <map>
#include <string>

#include "StepperUnit.h"
#include "Relay.h"
#include "Solenoids.h"

int main()
{

    StepperUnit::change = true;
    Relay::change = true;
    Solenoids::change = true;

    enum strictness {Liberal, Conservitive};

    // Adjustments
    int c25_adj = 5;
    int c10_adj = 1;
    int c5_adj = 2;
    int ball_3_5_adj = 5;
	int spacelabRocketSpecial_adj = 1;
	bool match_adj = false;
	strictness spaceLab_adj = Conservitive;

    std::map<std::string, Relay> re = 
    {   {"a", Relay("a")},
        {"b",Relay("b")},
        {"ballIndex",Relay("ballIndex")},
        {"bonus",Relay("bonus")},
        {"captiveBall",Relay("captiveBall")},
        {"change",Relay("change")},
        {"coin",Relay("coin")},
        {"doubleBonus",Relay("doubleBonus")},
        {"fiveBallInline",Relay("fiveBallInline")},
        {"c5",Relay("c5")},
        {"c10",Relay("c10")},
        {"c25",Relay("c25")},
        {"pt50",Relay("pt50")},
        {"gameOver",Relay("gameOver")},
        {"game",Relay("game")},
        {"pt100000",Relay("pt100000")},
        {"k",Relay("k")},
        {"l",Relay("l")},
        {"lock",Relay("lock")},
        {"outHole",Relay("outHole")},
        {"reset",Relay("reset")},
        {"rocketSpecial",Relay("rocketSpecial")},
        {"s",Relay("s")},
        {"scoreReset",Relay("scoreReset")},
        {"skyLab",Relay("skyLab")},
        {"spaceLab",Relay("spaceLab")},
        {"spaceLabSpecial",Relay("spaceLabSpecial")},
        {"pt10",Relay("pt10")},
        {"pt100",Relay("pt100")},
        {"pt1000",Relay("pt1000")},
		{"y",Relay("y")}
    };

    // Score Motor
    // Score Motor switches 5 and 6 are the same position.
    //int scoreMotor = 0;         // E-4
    bool impulse = false;

    std::map<std::string, StepperUnit> steppers = 
    { 
        { "advanceCount", StepperUnit("advanceCount",9) },
        { "alternator", StepperUnit("alternator",2) },
        { "ballCount", StepperUnit("ballCount",5) },
        { "noMatch", StepperUnit("noMatch",10) },
		{ "credit", StepperUnit("credit",9) },
        { "pt10", StepperUnit("pt10",9,StepperUnit::Continuous) },
        { "pt100", StepperUnit("pt100",9, StepperUnit::Continuous) },
        { "pt1000", StepperUnit("pt1000",9, StepperUnit::Continuous) },
		{ "pt10000", StepperUnit("pt10000",9, StepperUnit::Continuous) },
        { "scoreMotor", StepperUnit("scoreMotor",5, StepperUnit::Continuous) }
    };

    // Alternator Unit
    int alternatorUnit = 0;             // E-2
    bool altUnit_eos = false;          // TODO: altUnit_eos - Don't know what value;

    // SkyLab Unit Stepper
    bool skyLabResetUnit = false;      // D-1

    // Solenoids
    std::map<std::string, Solenoids> sol =
    {
        {"ballRelease", Solenoids("ballRelease")},
        {"coinLockout", Solenoids("coinLockout")},
        {"knocker", Solenoids("knocker")},
        //{"leftFlipper", Solenoids("leftFlipper")},
        //{"leftJetBumper", Solenoids("leftJetBumper")},
        //{"largeChime", Solenoids("largeChime")},
        //{"mediumChime", Solenoids("mediumChime")},
        //{"smallChime", Solenoids("smallChime")},
        { "totalPaymeter", Solenoids("totalPaymeter")}
    };


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
    bool left4CaptiveBall_sw = false;  // D-12
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
    bool leftRolloverButton_sw = false; // E-16
    bool rightRolloverButton_sw = false; // E-16

    // Odd Items
	bool c5_re_last = false;


	for (int step = 0; step < 20; ++step)
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
        if (step == 7)
            creditButton_sw = true;
        if (step == 8)
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
            if (re["c5"] && !c5_re_last)
            {
                alternatorUnit = alternatorUnit == 0 ? 1 : 0;
				if (settle == 0) altUnit_eos = true;
                
            }
            if (settle == 0 && altUnit_eos) altUnit_eos = false;

            c5_re_last = re["c5"];
            //std::cout << "alternatorUnit = " << alternatorUnit << "\n";

            // 25 Cent Logic
            bool r_br = steppers["scoreMotor"] != 6;
            bool r_y_3 = steppers["scoreMotor"] != 4 && r_br;
            bool br_b = steppers["scoreMotor"] != 3 && r_y_3;
            bool blu_b = steppers["scoreMotor"] != 2 && br_b;
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
            re["c25"] = (re["c25"] && y_b_1) || r_o;
            std::cout << re["c25"];

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
            bool r_b = blu_y && re["c10"];

            bool blu_br = !antiCheat_sw && c10_sw;
            switch (c10_adj) {
            case 2:
            case 3:
                re["c10"] = blu_br || r_b;
                break;
            default:
                re["c10"] = false;
                break;
            }
            std::cout << re["c10"];

            // Section 3
            // Coin Relay Logic
            bool w_b = !antiCheat_sw
                && c5_sw;
            bool g_w_1 = (w_b && (c5_adj == 1));
            g_w_1 = g_w_1 || blu_br && (c10_adj == 1);
            bool r_w = (steppers["scoreMotor"] != 3 && ball_3_5_adj == 3)
                || (steppers["scoreMotor"] != 5 && ball_3_5_adj == 5)
                || re["game"];
            g_w_1 = g_w_1 || (r_w && re["coin"]);
            g_w_1 = g_w_1 || (alternatorUnit == 2 && re["c5"]);
            bool w_grey = /*scoreMotor != 0*/steppers["scoreMotor"] == 0
                && (steppers["ballCount"] == 0 || re["game"]);
            g_w_1 = g_w_1
                || (steppers["credit"] == 0
                    && creditButton_sw);
            re["coin"] = w_b || g_w_1;
            std::cout << re["coin"];

            // 5 Cent Logic
            re["c5"] = (altUnit_eos && re["c5"])
                || (c5_adj == 2 && w_b);
            std::cout << re["c5"];

            // Coin Lockout Solenoid Logic
            sol["coinLockout"] = (steppers["credit"] != 0) && !w_grey;
            std::cout << sol["coinLockout"];

            // Reset Relay Logic
            bool blu_br_1 = re["bonus"] || /*(scoreMotor == 0) */ (steppers["scoreMotor"] != 0);
            blu_br_1 = blu_br_1
                || (steppers["pt10"] != 0 && steppers["pt100"] != 0 && steppers["pt1000"] != 0 && steppers["pt10000"] != 0);
            bool y_blu_2 = blu_br_1 && (!re["game"] && !re["lock"]);
            bool blu_w_1 = blu_br_1 && re["reset"];
            re["reset"] = y_blu_2 || blu_w_1 || re["coin"];
            std::cout << re["reset"];

            // Section 4
            // Lock Relay Logic
            re["lock"] = !kickOff_sw
                && (steppers["scoreMotor"] == 1
                    || leftFlipper_sw
                    || re["c5"]
                    || re["lock"]);
            std::cout << re["lock"];

            // Score Motor Advance Logic
            //bool r_b_2 = re["coin"] && !impulse;
            //bool br_b_1 = leftFlipper_sw && !impulse;
            //scoreMotor += (r_b_2 || br_b_1) ? 1 : 0;
            //scoreMotor = (scoreMotor > 6) ? 0 : scoreMotor;

            if (settle == 0)
            {
                // Score Motor Logic
                if (re["rocketSpecial"]
                    || re["spaceLabSpecial"]
                    || re["skyLab"]
                    || re["bonus"]
                    || re["reset"]
                    || steppers["scoreMotor"] != 0
                    || re["pt50"]
                    || re["outHole"]
                    || (g_o && re["c10"])
                    || (g_o && re["c25"]))
                {
					steppers["scoreMotor"]++;
                    //scoreMotor += 1;
                    impulse = steppers["scoreMotor"].eos();
                }
       //         else
       //         {
       //             impulse = false;
    			//}
            }
            impulse = steppers["scoreMotor"].eos();
            std::cout << steppers["scoreMotor"];
            //else
            //{
            //    impulse = false;
            //}

            //std::cout << "scoreMotor = " << scoreMotor << "\n";
            //std::cout << "impulse = " << impulse << "\n";

            //Knocker Solenoid Logic
            bool o_r = g_o && !re["c25"] && !re["c10"] && re["coin"];
            bool b_w = re["spaceLabSpecial"] && steppers["scoreMotor"] == 5
                || re["rocketSpecial"] && steppers["scoreMotor"] == 1
                || steppers["credit"].eos()
                || steppers["ballCount"].eos();
            sol["knocker"] = o_r && b_w;
            std::cout << sol["knocker"];

            //Section 5
            // Score Drum Units Logic
            if (re["pt10"] || (re["scoreReset"] && steppers["pt10"] != 0))
            {
                steppers["pt10"]++;
            }
			std::cout << steppers["pt10"];

            if (re["pt100"] || (re["scoreReset"] && steppers["pt100"] != 0))
            {
                steppers["pt100"]++;
            }
            std::cout << steppers["pt100"];

            if (re["pt1000"] || (re["scoreReset"] && steppers["pt1000"] != 0))
            {
                steppers["pt1000"]++;
            }
            std::cout << steppers["pt1000"];

            bool b_o_1 = (re["scoreReset"] && steppers["pt10000"] != 0);
            if (b_o_1 || steppers["pt1000"] == 9000)
            {
                steppers["pt10000"]++;
            }
            std::cout << steppers["pt1000"];

            // Game Relay Logic
            bool game_re_trip = re["ballIndex"] && !re["game"];
            bool r_g_1 = re["coin"];                       // Continued in Section 6
            bool r_blu = r_g_1 && steppers["ballCount"] == 0;
            bool game_re_latch = r_blu && steppers["scoreMotor"] == 0;
            sol["totalPaymeter"] = game_re_latch;
			if (game_re_latch) steppers["credit"].reset();
            if (game_re_trip)
                re["game"] = false;
            else if (game_re_latch)
                re["game"] = true;
            //std::cout << "game_re_latch = " << game_re_latch << "\n";
            //std::cout << "game_re_trip = " << game_re_trip << "\n";
            std::cout << re["game"];
            std::cout << sol["totalPaymeter"];
            std::cout << steppers["credit"];

            // Section 6
            // Game Over Relay Logic
            bool blu_y_1 = re["outHole"] && re["ballIndex"] && steppers["scoreMotor"] == 0;
            bool gameOver_re_latch = r_g_1 || (steppers["ballCount"] > 1) && blu_y_1;
            bool grey_g = re["outHole"];
            bool g_b_3 = grey_g && re["ballIndex"];
            bool b_y_1 = g_b_3
                && steppers["scoreMotor"] == 1
                && (steppers["ballCount"] == 0 || steppers["ballCount"] == 1);
            bool blu_r_1 = !re["gameOver"] && (!re["lock"] || tilt_sw);
            bool gameOver_re_trip = blu_r_1 || b_y_1;
            if (gameOver_re_trip)
                re["gameOver"] = false;
            else if (gameOver_re_latch)
                re["gameOver"] = true;
            std::cout << re["gameOver"];

            // Ball Count Unit Logic
            bool o_r_1 = g_b_3 && steppers["scoreMotor"] == 2;
            bool b_w_4 = g_b_3 && impulse;
            bool grey_b = b_w_4 && !re["game"];
            o_r_1 = o_r_1 || (b_w_4 && re["game"]);
			if (o_r_1) steppers["ballCount"].reset();
			// Increment Ball Count Unit
            grey_b = b_w_4 && !re["game"];
            if (grey_b)
            {
                steppers["ballCount"]++;
            }
            
            std::cout << steppers["ballCount"];

            // Section 7
            // Ball Release Solenoid
            if (!re["reset"] && !re["gameOver"]) // RED Wire
            {
                sol["ballRelease"] = grey_g && steppers["scoreMotor"] == 4;
            }
            std::cout << sol["ballRelease"];

            // Score Reset Relay
            bool grey_w_3 = impulse;
            re["scoreReset"] = grey_w_3 && re["reset"];
            std::cout << re["scoreReset"];

            // Credit Unit
            bool grey = grey_w_3 && (re["c10"] || re["c25"]);
            if (grey && !steppers["credit"].eos())
            {
                steppers["credit"]++;
            }
			std::cout << steppers["credit"];

            // Section 8
            // Spacelab & Rocket Special adjustments
            // TODO: This logic needs to be located in a prior section to properly affect the ball/credit count
            bool br_3 = !re["outHole"];
            bool grey_o_1 = br_3 && re["spaceLabSpecial"] && steppers["scoreMotor"] == 5;
            bool br_g_2 = br_3 && re["rocketSpecial"] && steppers["scoreMotor"] == 1;
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
            bool r_b_5 = steppers["ballCount"] == 1;
            bool r_b_4 = r_b_5 && re["ballIndex"] && re["outHole"] && steppers["scoreMotor"] == 0;
            bool blu_o_2 = r_b_4 && steppers["pt10"] == steppers["noMatch"] && match_adj;
            // High Score Unit Logic
            // TODO: High Score Unit Logic needs to be implemented

            // Section 9
            // Double Bonus Relay Logic
            bool r_g_5 = re["doubleBonus"] || (r_b_5 && !re["ballIndex"]);
            re["doubleBonus"] = r_g_5;
            std::cout << re["doubleBonus"];

            // Advance Unit Stepper Logic (Reset)
            bool r_blu_2 = (r_y_3 && steppers["scoreMotor"] == 3 && !re["doubleBonus"])
				|| steppers["scoreMotor"] == 5; // Was 6, 5 and 6 are the same position
            if (r_blu_2 && re["bonus"])
				steppers["advanceCount"].reset();
            std::cout << steppers["advanceCount"];

            // Bonus Relay
            bool grey_blu = steppers["advanceCount"] != 0 && (re["reset"] || re["bonus"]);
            bool w_blu_1 = steppers["scoreMotor"] == 0;
            bool g_w_2 = w_blu_1 && steppers["ballCount"] != 0;
            re["bonus"] = (g_w_2 && steppers["advanceCount"] != 0 && re["outHole"]) || grey_blu;
            std::cout << re["bonus"];
            if (!re["reset"]) // BLUE - Yellow - White Wire
            {

                // Outhole Relay
                bool blu_y_4 = g_w_2 && steppers["advanceCount"] == 0 && re["bonus"];
                re["outHole"] = (steppers["scoreMotor"] == 0 && re["outHole"]) || blu_y_4;
                std::cout << re["outHole"];

                // Ball Index Relay
                bool o = w_blu_1 && re["gameOver"] && re["outHole"];
                o = o || ((steppers["advanceCount"] == 1
                    || steppers["advanceCount"] == 2
                    || steppers["advanceCount"] == 3)
                    &&
                    (re["pt10"] || re["pt100"] || re["pt1000"]));
                bool w_r_1 = !re["outHole"] || steppers["scoreMotor"] == 3;
                re["ballIndex"] = o || (w_r_1 && re["ballIndex"]);
                std::cout << re["ballIndex"];

                // Section 10
                // 5 Ball Inline Relay Logic
                re["fiveBallInline"] = w_r_1 && (re["rocketSpecial"] || re["spaceLabSpecial"]);
                std::cout << re["fiveBallInline"];

                // 100000 Point Relay Logic
                re["pt100000"] = re["pt100000"] || (steppers["pt10000"] == 9 && steppers["pt1000"] == 9);
                std::cout << re["pt10000"];
            }

            if (!re["reset"] && !re["gameOver"]) // RED Wire
            {
                // Change Relay Logic
                re["change"] = steppers["noMatch"] % 2 == 1;
                std::cout << re["change"] ;

                // S Relay Logic
                re["s"] = sStandup_sw && !re["s"];
                bool g_b = kStandup_sw && re["k"];
                std::cout << re["s"];

                // Section 11
                // K Relay Logic
                re["k"] = kStandup_sw && !re["k"];
                bool br_b_1 = yStandup_sw && re["y"];
                std::cout << re["k"];

                // Y Relay Logic
                re["y"] = yStandup_sw && !re["y"];
                br_b_1 = br_b_1 || (lStandup_sw && re["l"]);
                std::cout << re["y"];

                // L Relay Logic
                re["l"] = lStandup_sw && !re["l"];
                g_b = g_b || (aStandup_sw && re["a"]);
                std::cout << re["l"];

                // A Relay Logic
                re["a"] = aStandup_sw && !re["a"];
                br_b_1 = br_b_1 || (bStandup_sw && re["b"]);
                std::cout << re["a"];

                // B Relay Logic
                re["b"] = bStandup_sw && !re["b"];
                br_b_1 = br_b_1 || bStandup_sw && re["b"];
                std::cout << re["b"];

                // 50 Point Relay Logic
                bool br_1 = steppers["scoreMotor"] != 5;
                re["pt50"] = (br_1 && re["pt50"]) || br_b_1;

                // section 12
                // Rocket Special Relay Logic
                bool y_0 = !left1CaptiveBall_sw
                    && right3CaptiveBall_sw
                    && right4CaptiveBall_sw;
                bool y_g = !right1CaptiveBall_sw
                    && left3CaptiveBall_sw
                    && left4CaptiveBall_sw;
                bool g_r_1 = (re["captiveBall"] && y_0) || (!re["captiveBall"] && y_g);
                re["rocketSpecial"] = (g_r_1 && re["fiveBallInline"])
                    || (br_1 && re["rocketSpecial"]);
                std::cout << re["rocketSpecial"];

                // SkyLab Relay Logic
                bool g_y = br_1 && re["skyLab"];
                re["skyLab"] = g_y ||
                    (steppers["scoreMotor"] == 1 && re["s"] && re["k"] && re["y"] && re["l"] && re["a"] && re["b"]);
                std::cout << re["skyLab"];
   //         }
   //         // Back to BLACK wire
			//// Captive Ball Relay Logic
   //         bool b_blu = steppers["scoreMotor"] != 0
   //             && (re["coin"]
   //                 || re["gameOver"]
   //                 || re["rocketSpecial"]);
   //         captiveBall_re_latch = b_blu && left2CaptiveBall_sw;
			//captiveBall_re_trip = b_blu && right2CaptiveBall_sw;
   //         if (captiveBall_re_trip)
   //             captiveBall_re = false;
   //         else if (captiveBall_re_latch)
			//	captiveBall_re = true;
   //         std::cout << "captiveBall_re_latch = " << captiveBall_re_latch << "\n";
   //         std::cout << "captiveBall_re_trip = " << captiveBall_re_trip << "\n";
			//std::cout << "captiveBall_re = " << captiveBall_re << "\n";

   //         if (!re["reset"] && !re["gameOver"]) // RED Wire
   //         {
                // Section 13
				// SpaceLab Relay Logic
                bool w_grey_2 =
                    (spacelabRocketSpecial_adj == Liberal && steppers["advanceCount"] == 5)
                    && (spacelabRocketSpecial_adj == Conservitive && steppers["advanceCount"] == 7)
                    && steppers["advanceCount"].eos();
                re["spaceLab"] = w_grey_2 
					|| (steppers["scoreMotor"] != 4 || !re["spaceLabSpecial"])
                    && re["spaceLab"];
				std::cout << re["spaceLab"];

				// SpaceLab Special Relay Logic
				bool g_1 = r_br && re["spaceLabSpecial"];
                bool b_r = (leftBotOutsideRollover_sw && !re["change"])
                    || (rightBotOutsideRollover_sw && re["change"]);
                bool br_y = (leftBotOutsideRollover_sw && re["change"])
					|| (rightBotOutsideRollover_sw && !re["change"]);
                re["spaceLabSpecial"] = (b_r && re["spaceLab"])
                    || g_1;
                std::cout << re["spaceLabSpecial"];
                br_y = br_y || (b_r && !re["spaceLab"]);

				// 10 Point Relay Logic
				g_b = g_b || steppers["pt10"].eos() && re["pt10"];
				g_b = g_b || leftKickerCount_sw || rightKickerCount_sw;
				g_b = g_b || (steppers["scoreMotor"] == 5 || impulse) || re["pt50"]; // Was 6, 5 and 6 are the same position
                re["pt10"] = g_b;
				std::cout << re["pt10"];

                // Section 14
				// 1000 Point Relay Logic
				br_y = br_y || (steppers["scoreMotor"] == 5 || impulse) && re["bonus"]; // Was 6, 5 and 6 are the same position
                br_y = br_y || br_3 && steppers["advanceCount"].eos();
                br_y = br_y || steppers["pt1000"].eos() && re["pt1000"];
				bool o_b_3 = (right4CaptiveBall_sw && !re["captiveBall"])
                    || (left4CaptiveBall_sw && re["captiveBall"]);
                re["pt1000"] = br_y 
                    || (o_b_3 && re["fiveBallInline"])
                    || (o_b_3 && !re["fiveBallInline"] && re["spaceLab"]);
				std::cout << re["pt1000"];

				// 100 Point Relay Logic
                bool w_r = o_b_3 && !re["fiveBallInline"] && !re["spaceLab"];
				w_r = w_r || rightJetBumper_sw || leftJetBumper_sw;
                w_r = w_r || steppers["noMatch"].eos();
                w_r = w_r || steppers["pt10"] == 9 && re["pt10"];
				w_r = w_r || !steppers["pt100"].eos() && re["pt100"];
                bool g_4 = leftTopRollover_sw || rightBottomRollover_sw;
				bool grey_w = rightTopRollover_sw || leftBottomRollover_sw;
				w_r = w_r || g_4 && re["change"] || grey_w && !re["change"];
				re["pt100"] = w_r;
				std::cout << re["pt100"];

                // Section 15
				// Advance Unit Stepper Logic (Count)
                bool grey_y_1 = grey_g && steppers["scoreMotor"] == 3;
                grey_y_1 = grey_y_1 
                    || (steppers["scoreMotor"] == 3 
                    || steppers["scoreMotor"] == 4) && re["skyLab"];
                grey_y_1 = grey_y_1 || g_4 && re["change"] || grey_w && !re["change"];
                if (grey_y_1)
                {
                    steppers["advanceCount"]++;
                }

                // No Match Unit Stepper Logic
                if (leftRolloverButton_sw || rightRolloverButton_sw)
                {
                    steppers["noMatch"]++;
				}


            }

            // Section 12
            // Back to BLACK wire
            // Captive Ball Relay Logic
            bool b_blu = steppers["scoreMotor"] != 0
                && (re["coin"]
                    || re["gameOver"]
                    || re["rocketSpecial"]);
            bool captiveBall_re_latch = b_blu && left2CaptiveBall_sw;
            bool captiveBall_re_trip = b_blu && right2CaptiveBall_sw;
            if (captiveBall_re_trip)
                re["captiveBall"] = false;
            else if (captiveBall_re_latch)
                re["captiveBall"] = true;
            std::cout << re["captiveBall"];

        }
        for (auto& pair : steppers) 
            pair.second.ResetEos();
    }




    //ballCountResetUnit = g_b_3 && scoreMotor == 2;
	//steppers["ballCount"] = b_w_4 || re["game"] ? 0 : steppers["ballCount"];
 //   bool grey_b = b_w_4 && !re["game"];
	//steppers["ballCount"] += grey_b ? 1 : 0;



    
    //gameOver_re_trip = blu_r_1 || blu_y_1; // This is latched logic

    //re["lock"] = !kickOff_sw || scoreMotor == 1 || leftFlipper_sw || re["lock"];

    //bool b_w_4 = re["coin"] && impulse;
    //ballCountResetUnit = g_b_3 && scoreMotor == 2 || (b_w_4 && re["game"]);








    // Section 4 Latched Logic

    //std::cout << "Hello World!\n";
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
