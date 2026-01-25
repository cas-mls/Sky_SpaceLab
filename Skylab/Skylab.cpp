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

    bool change = true;

    enum strictness {Liberal, Conservitive};

    // Adjustments
    int c25_adj = 5;
    int c10_adj = 1;
    int c5_adj = 2;
    int ball_3_5_adj = 5;
	int spacelabRocketSpecial_adj = 1;
	bool match_adj = false;
	strictness spaceLab_adj = Liberal;

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
		{"y",Relay("y")},
        { "SkylabBankReset", Relay("SkylabBankReset")}
    };
    std::map<std::string, Relay> reA(re);


    // Score Motor
    // Score Motor switches 5 and 6 are the same position.
    //int scoreMotor = 0;         // E-4
    bool impulse = false;

    std::map<std::string, StepperUnit> units = 
    { 
        { "advanceCount", StepperUnit("advanceCount",9) },
        { "alternator", StepperUnit("alternator",2) },
        { "ballCount", StepperUnit("ballCount",5, StepperUnit::UpDown) },
        { "noMatch", StepperUnit("noMatch",10, StepperUnit::Continuous) },
		{ "credit", StepperUnit("credit",9, StepperUnit::UpDown) },
        { "pt10", StepperUnit("pt10",9, StepperUnit::Continuous) },
        { "pt100", StepperUnit("pt100",9, StepperUnit::Continuous) },
        { "pt1000", StepperUnit("pt1000",9, StepperUnit::Continuous) },
		{ "pt10000", StepperUnit("pt10000",9, StepperUnit::Continuous) },
        { "scoreMotor", StepperUnit("scoreMotor",5, StepperUnit::Continuous) }
    };

    std::map<std::string, StepperUnit> unitsA(units);


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
        { "totalPaymeter", Solenoids("totalPaymeter")},
        { "SkylabBankReset", Solenoids("SkylabBankReset")}
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
    bool outHole_sw = false; // D-9

    // Odd Items
	bool c5_re_last = false;


	for (int step = 0; step < 50; ++step)
    {
        std::cout << "***** step = " << step << "\n";
        //re = reA;
        //units = unitsA;

        //if (step == 1)
        //    leftFlipper_sw = true;          // E-4
        //if (step == 2)
        //{
        //    leftFlipper_sw = false;          // E-4
        //    //c10_sw = true;          // D-2
        //}
        if (step == 0)
        {
			reA["lock"] = true;
            reA["coin"] = false;
            reA["game"] = true;
            reA["gameOver"] = false;
			reA["reset"] = false; 
            reA["scoreReset"] = false;
			unitsA["ballCount"] = 5;
			unitsA["credit"] = 5; 
        }
        if (step == 3)
        {
            //kStandup_sw             = true;          // D-2
            //yStandup_sw             = true;          // D-2
            //lStandup_sw             = true;          // D-2
            //aStandup_sw             = true;          // D-2
			//bStandup_sw             = true;          // D-2
            //leftKickerCount_sw      = true; // D-13
            //rightKickerCount_sw     = true; // D-13
            //leftJetBumper_sw        = true; // E-14
            //rightJetBumper_sw       = true; // E-14
            //leftTopRollover_sw = true;  // E-15  *****
            rightBottomRollover_sw  = true; // E-15
            //rightTopRollover_sw     = true; // E-15
            //leftBottomRollover_sw   = true;  // E-15
            //leftRolloverButton_sw   = true; // E-16
            //rightRolloverButton_sw  = true; // E-16
        }
        if (step == 5)
        {
            //kStandup_sw             = false;          // D-2
            //yStandup_sw             = false;          // D-2
            //lStandup_sw             = false;          // D-2
            //aStandup_sw             = false;          // D-2
            //bStandup_sw             = false;          // D-2
            //leftKickerCount_sw      = false; // D-13
            //rightKickerCount_sw     = false; // D-13
            //leftJetBumper_sw        = false; // E-14
            //rightJetBumper_sw       = false; // E-14
            //leftTopRollover_sw      = false;  // E-15 *****
            rightBottomRollover_sw  = false; // E-15
            //rightTopRollover_sw     = false; // E-15
            //leftBottomRollover_sw   = false;  // E-15
            //leftRolloverButton_sw   = false; // E-16
            //rightRolloverButton_sw  = false; // E-16
        }
        if (step == 7)
            rightBottomRollover_sw = true; // E-15
        if (step == 9)
            rightBottomRollover_sw = false; // E-15
        //if (step == 11)
        //    rightBottomRollover_sw = true; // E-15
        //if (step == 13)
        //    rightBottomRollover_sw = false; // E-15
        //if (step == 15)
        //    rightBottomRollover_sw = true; // E-15
        //if (step == 17)
        //    rightBottomRollover_sw = false; // E-15
        //if (step == 19)
        //    rightBottomRollover_sw = true; // E-15
        //if (step == 21)
        //    rightBottomRollover_sw = false; // E-15
        if (step == 25)
            outHole_sw = true;
        //if (step == 23)
        //    rightBottomRollover_sw = true; // E-15
        //if (step == 25)
        //    rightBottomRollover_sw = false; // E-15
        //if (step == 27)
        //    rightBottomRollover_sw = true; // E-15
        //if (step == 29)
        //    rightBottomRollover_sw = false; // E-15
        //if (step == 31)
        //    rightBottomRollover_sw = true; // E-15
        //if (step == 33)
        //    rightBottomRollover_sw = false; // E-15



        if (step == 20)
        {
            //sStandup_sw = true;          // D-2
        }
        if (step == 22)
        {
            //sStandup_sw = false;          // D-2
        }

        //std::string tmpOut = unitsA["pt10"].PrintEos(units["pt10"], false);
        //if (tmpOut != "")
        //    std::cout << "Prior Copy" << tmpOut << "\n";
        
        // Load previous assigned state
        for (auto& pair : unitsA)
        {
			std::string key = pair.first;
            units[key].Assign(pair.second);
            pair.second.AssignEos(units[key]); // Update the eos
        }
        for (auto& pair : reA)
        {
            std::string key = pair.first;
            re[key].Assign(pair.second);
        }

        //tmpOut = unitsA["pt10"].PrintEos(units["pt10"], false);
        //if (tmpOut != "")
        //    std::cout << "After Copy" << tmpOut << "\n";


            // Section 2
            // Alternator Unit Logic
    //        if (re["c5"] && !c5_re_last)
    //        {
    //            alternatorUnit = alternatorUnit == 0 ? 1 : 0;
				//if (settle == 0) altUnit_eos = true;
    //            
    //        }
    //        if (settle == 0 && altUnit_eos) altUnit_eos = false;

        c5_re_last = re["c5"];

        // 25 Cent Logic
        bool r_br = units["scoreMotor"] != 6;
        bool r_y_3 = units["scoreMotor"] != 4 && r_br;
        bool br_b = units["scoreMotor"] != 3 && r_y_3;
        bool blu_b = units["scoreMotor"] != 2 && br_b;
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
        reA["c25"] = (re["c25"] && y_b_1) || r_o;

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
            reA["c10"] = blu_br || r_b;
            break;
        default:
            reA["c10"] = false;
            break;
        }

        // Section 3
        // Coin Relay Logic
        bool w_b = !antiCheat_sw
            && c5_sw;
        bool g_w_1 = (w_b && (c5_adj == 1));
        g_w_1 = g_w_1 || blu_br && (c10_adj == 1);
        bool r_w = (units["scoreMotor"] != 3 && ball_3_5_adj == 3)
            || (units["scoreMotor"] != 5 && ball_3_5_adj == 5)
            /* || re["game"]*/;
        g_w_1 = g_w_1 || (r_w && re["coin"]);
        g_w_1 = g_w_1 || (alternatorUnit == 2 && re["c5"]);
        bool w_grey = /*scoreMotor != 0*/units["scoreMotor"] == 0
            && (units["ballCount"] == 0 || !re["game"]);
        g_w_1 = g_w_1 || w_grey
            || (units["credit"] != 0
                && creditButton_sw);
        bool coin_re = w_b || g_w_1;
        reA["coin"] = w_b || g_w_1;

        // 5 Cent Logic
        reA["c5"] = (altUnit_eos && re["c5"])
            || (c5_adj == 2 && w_b);

        // Coin Lockout Solenoid Logic
        sol["coinLockout"] = (units["credit"] == 0) && w_grey;

        // Reset Relay Logic
        int tmp = units["scoreMotor"];
        bool blu_br_1 = re["bonus"] || /*(scoreMotor == 0) */ (units["scoreMotor"] != 0);
        blu_br_1 = blu_br_1
            || (units["pt10"] != 0 && units["pt100"] != 0 && units["pt1000"] != 0 && units["pt10000"] != 0);
        bool y_blu_2 = blu_br_1 && (!re["game"] && !re["lock"]);
        bool blu_w_1 = blu_br_1 && re["reset"];
        bool reset_re = y_blu_2 || blu_w_1 || re["coin"];
        reA["reset"] = y_blu_2 || blu_w_1 || re["coin"];

        // Section 4
        // Lock Relay Logic
        reA["lock"] = !kickOff_sw
            && (units["scoreMotor"] == 1
                || leftFlipper_sw
                || re["c5"]
                || re["lock"]);

        // Score Motor Advance Logic
        //bool r_b_2 = re["coin"] && !impulse;
        //bool br_b_1 = leftFlipper_sw && !impulse;
        //scoreMotor += (r_b_2 || br_b_1) ? 1 : 0;
        //scoreMotor = (scoreMotor > 6) ? 0 : scoreMotor;

        if (!impulse)
        {
                // Score Motor Logic
            if (re["rocketSpecial"]
                || re["spaceLabSpecial"]
                || re["skyLab"]
                || re["bonus"]
                || re["reset"]
                || units["scoreMotor"] != 0
                || re["pt50"]
                || re["outHole"]
                || (g_o && re["c10"])
                || (g_o && re["c25"]))
            {
                unitsA["scoreMotor"]++;
                impulse = true;
            }
        }
        else
        {
            impulse = false;
        }

        //Knocker Solenoid Logic
        bool o_r = g_o && !re["c25"] && !re["c10"] && !re["coin"];
        bool b_w = re["spaceLabSpecial"] && units["scoreMotor"] == 5
            || re["rocketSpecial"] && units["scoreMotor"] == 1
            || units["credit"].eos()
            || units["ballCount"].eos();
        sol["knocker"] = o_r && b_w;

        //Section 5
        // Score Drum Units Logic
        if (re["pt10"] || (re["scoreReset"] && units["pt10"] != 0))
        {
            unitsA["pt10"]++;
        }

        if (re["pt100"] || (re["scoreReset"] && units["pt100"] != 0))
        {
            unitsA["pt100"]++;
        }

        if (re["pt1000"] || (re["scoreReset"] && units["pt1000"] != 0))
        {
            unitsA["pt1000"]++;
        }

        bool b_o_1 = (re["scoreReset"] && units["pt10000"] != 0);
        if (b_o_1 || units["pt1000"] == 9000)
        {
            unitsA["pt10000"]++;
        }

        // Game Relay Logic
        bool game_re_trip = re["ballIndex"] && !re["game"];
        bool r_g_1 = re["coin"];                       // Continued in Section 6
        bool r_blu = r_g_1 && units["ballCount"] == 0;
        bool game_re_latch = r_blu && units["scoreMotor"] == 0;
        if (game_re_trip)
            reA["game"] = false;
            //reA["game"] = true;
        else if (game_re_latch)
            reA["game"] = true;
            //reA["game"] = false;
        sol["totalPaymeter"] = game_re_latch;
        if (game_re_latch) 
            unitsA["credit"]--;


        // Section 6
        // Game Over Relay Logic
        bool blu_y_1 = re["outHole"] && re["ballIndex"] && units["scoreMotor"] == 0;
        bool gameOver_re_latch = r_g_1 || (units["ballCount"] > 1) && blu_y_1;
        bool grey_g = re["outHole"];
        bool g_b_3 = grey_g && re["ballIndex"];
        bool b_y_1 = g_b_3
            && units["scoreMotor"] == 1
            && (units["ballCount"] == 0 || units["ballCount"] == 1);
        bool blu_r_1 = !re["gameOver"] && (!re["lock"] || tilt_sw);
        bool gameOver_re_trip = blu_r_1 || b_y_1;
        if (gameOver_re_trip)
            reA["gameOver"] = false;
        else if (gameOver_re_latch)
            reA["gameOver"] = true;

        // Ball Count Unit Logic
        bool o_r_1 = g_b_3 && units["scoreMotor"] == 2;
        bool b_w_4 = r_g_1 && impulse;
        bool grey_b = b_w_4 && !re["game"];
        o_r_1 = o_r_1 || (b_w_4 && re["game"]);
        // Decrement Ball Count Unit
        if (o_r_1)
            unitsA["ballCount"]--;
		// Increment Ball Count Unit
        if (grey_b)
            unitsA["ballCount"]++;

        // Section 7
        // Ball Release Solenoid
        if (!re["reset"] && !re["gameOver"]) // RED Wire
        {
            sol["ballRelease"] = grey_g && units["scoreMotor"] == 4;
        }

        // Score Reset Relay
        bool grey_w_3 = impulse;
        reA["scoreReset"] = grey_w_3 && re["reset"];

        // Credit Unit
        bool grey = grey_w_3 && (re["c10"] || re["c25"]);
        if (grey && !units["credit"].eos())
        {
            unitsA["credit"]++;
        }

        // Section 8
        // Spacelab & Rocket Special adjustments
        // TODO: This logic needs to be located in a prior section to properly affect the ball/credit count
        bool br_3 = !re["outHole"];
        bool grey_o_1 = br_3 && re["spaceLabSpecial"] && units["scoreMotor"] == 5;
        bool br_g_2 = br_3 && re["rocketSpecial"] && units["scoreMotor"] == 1;
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
        bool r_b_5 = units["ballCount"] == 1;
        bool r_b_4 = r_b_5 && re["ballIndex"] && re["outHole"] && units["scoreMotor"] == 0;
        bool blu_o_2 = r_b_4 && units["pt10"] == units["noMatch"] && match_adj;

        // High Score Unit Logic
        // TODO: High Score Unit Logic needs to be implemented

        // Section 9
        // Double Bonus Relay Logic
        bool r_g_5 = re["doubleBonus"] || (r_b_5 && !re["ballIndex"]);
        reA["doubleBonus"] = r_g_5;

        // Advance Unit Stepper Logic (Reset)
        bool r_blu_2 = (r_y_3 && units["scoreMotor"] == 3 && !re["doubleBonus"])
			|| units["scoreMotor"] == 5; // Was 6, 5 and 6 are the same position
        if (r_blu_2 && re["bonus"])
			unitsA["advanceCount"].reset();

        // Bonus Relay
        bool grey_blu = units["advanceCount"] != 0 && (re["reset"] || re["bonus"]);
        bool w_blu_1 = units["scoreMotor"] == 0;
        bool g_w_2 = w_blu_1 && units["ballCount"] != 0;
        reA["bonus"] = grey_blu || (g_w_2 && units["advanceCount"] != 0 && outHole_sw);
        if (!re["reset"]) // BLUE - Yellow - White Wire
        {

            // Outhole Relay
            bool blu_y_4 = g_w_2 && units["advanceCount"] == 0 && re["bonus"];
            reA["outHole"] = (units["scoreMotor"] == 0 && re["outHole"]) || blu_y_4;

            // Ball Index Relay
            bool o = w_blu_1 && re["gameOver"] && re["outHole"];
            o = o || ((units["advanceCount"] == 1
                || units["advanceCount"] == 2
                || units["advanceCount"] == 3)
                &&
                (re["pt10"] || re["pt100"] || re["pt1000"]));
            bool w_r_1 = !re["outHole"] || units["scoreMotor"] == 3;
            reA["ballIndex"] = o || (w_r_1 && re["ballIndex"]);

            // Section 10
            // 5 Ball Inline Relay Logic
            reA["fiveBallInline"] = w_r_1 && (re["rocketSpecial"] || re["spaceLabSpecial"]);

            // 100000 Point Relay Logic
            reA["pt100000"] = re["pt100000"] || (units["pt10000"] == 9 && units["pt1000"] == 9);
        }

        if (!re["reset"] && !re["gameOver"]) // RED Wire
        {
            // Change Relay Logic
            reA["change"] = units["noMatch"] % 2 == 1;

            // The S-K-Y-L-A-B are locking relays and release
            // when Skylab solenoid is activated.
            // S Relay Logic
            reA["s"] = sStandup_sw && !re["s"]
                || re["s"] && !re["SkylabBankReset"];
            bool g_b = sStandup_sw && re["s"];

            // Section 11
            // K Relay Logic
            reA["k"] = kStandup_sw && !re["k"]
                || re["k"] && !re["SkylabBankReset"];
            bool br_b_1 = kStandup_sw && re["k"];

            // Y Relay Logic
            reA["y"] = yStandup_sw && !re["y"]
                || re["y"] && !re["SkylabBankReset"];
            br_b_1 = br_b_1 || (yStandup_sw && re["y"]);

            // L Relay Logic
            reA["l"] = lStandup_sw && !re["l"]
                || re["l"] && !re["SkylabBankReset"];
            g_b = g_b || (lStandup_sw && re["l"]);

            // A Relay Logic
            reA["a"] = aStandup_sw && !re["a"]
                || re["a"] && !re["SkylabBankReset"];
            br_b_1 = br_b_1 || (aStandup_sw && re["a"]);

            // B Relay Logic
            reA["b"] = bStandup_sw && !re["b"]
                || re["b"] && !re["SkylabBankReset"];
            br_b_1 = br_b_1 || bStandup_sw && re["b"];

            // 50 Point Relay Logic
            bool br_1 = units["scoreMotor"] != 5;
            reA["pt50"] = (br_1 && re["pt50"]) || br_b_1;

            // section 12
            // Rocket Special Relay Logic
            bool y_0 = !left1CaptiveBall_sw
                && right3CaptiveBall_sw
                && right4CaptiveBall_sw;
            bool y_g = !right1CaptiveBall_sw
                && left3CaptiveBall_sw
                && left4CaptiveBall_sw;
            bool g_r_1 = (re["captiveBall"] && y_0) || (!re["captiveBall"] && y_g);
            reA["rocketSpecial"] = (g_r_1 && re["fiveBallInline"])
                || (br_1 && re["rocketSpecial"]);

            // SkyLab Relay Logic
            bool g_y = br_1 && re["skyLab"];
            reA["skyLab"] = g_y ||
                (units["scoreMotor"] == 0 && re["s"] && re["k"] && re["y"] && re["l"] && re["a"] && re["b"]);

			// Captive Ball Relay Logic
            // Back to BLACK wire see below ****

            // Section 13
			// SpaceLab Relay Logic
            bool w_grey_2 =
                (spaceLab_adj == Liberal && units["advanceCount"] == 5
                || spaceLab_adj == Conservitive && units["advanceCount"] == 7)
                && units["advanceCount"].eos();
            reA["spaceLab"] = w_grey_2 
				|| (units["scoreMotor"] != 4 || !re["spaceLabSpecial"])
                && re["spaceLab"];

			// SpaceLab Special Relay Logic
			bool g_1 = r_br && re["spaceLabSpecial"];
            bool b_r = (leftBotOutsideRollover_sw && !re["change"])
                || (rightBotOutsideRollover_sw && re["change"]);
            bool br_y = (leftBotOutsideRollover_sw && re["change"])
				|| (rightBotOutsideRollover_sw && !re["change"]);
            reA["spaceLabSpecial"] = (b_r && re["spaceLab"])
                || g_1;
            br_y = br_y || (b_r && !re["spaceLab"]);

			// 10 Point Relay Logic
			g_b = g_b || !units["pt10"].eos() && re["pt10"];
			g_b = g_b || leftKickerCount_sw || rightKickerCount_sw;
			g_b = g_b || (units["scoreMotor"] == 5 || impulse) || re["pt50"]; // Was 6, 5 and 6 are the same position
            reA["pt10"] = g_b;

            // Section 14
			// 1000 Point Relay Logic
			br_y = br_y || (units["scoreMotor"] == 5 || impulse) && re["bonus"]; // Was 6, 5 and 6 are the same position
            br_y = br_y || br_3 && units["advanceCount"].eos();
            br_y = br_y || !units["pt1000"].eos() && re["pt1000"];
			bool o_b_3 = (right4CaptiveBall_sw && !re["captiveBall"])
                || (left4CaptiveBall_sw && re["captiveBall"]);
            reA["pt1000"] = br_y 
                || (o_b_3 && re["fiveBallInline"])
                || (o_b_3 && !re["fiveBallInline"] && re["spaceLab"]);

			// 100 Point Relay Logic
            bool w_r = o_b_3 && !re["fiveBallInline"] && !re["spaceLab"];
			w_r = w_r || rightJetBumper_sw || leftJetBumper_sw;
            w_r = w_r || units["noMatch"].eos();
            w_r = w_r || units["pt10"] == 9 && re["pt10"];
			w_r = w_r || !units["pt100"].eos() && re["pt100"];
            bool g_4 = leftTopRollover_sw || rightBottomRollover_sw;
			bool grey_w = rightTopRollover_sw || leftBottomRollover_sw;
			w_r = w_r || g_4 && re["change"] || grey_w && !re["change"];
			reA["pt100"] = w_r;

            // Section 15
			// Advance Unit Stepper Logic (Count)
            bool grey_y_1 = grey_g && units["scoreMotor"] == 3;
            grey_y_1 = grey_y_1 
                || (units["scoreMotor"] == 3 
                || units["scoreMotor"] == 4) && re["skyLab"];
            grey_y_1 = grey_y_1 || g_4 && !re["change"] || grey_w && re["change"];
            if (grey_y_1)
            {
                unitsA["advanceCount"]++;
            }

            // No Match Unit Stepper Logic
            if (leftRolloverButton_sw || rightRolloverButton_sw)
            {
                unitsA["noMatch"]++;
			}


        }

        // Section 12
        // Back to BLACK wire
        // Captive Ball Relay Logic
        bool b_blu = units["scoreMotor"] != 0
            && (re["coin"]
                || re["gameOver"]
                || re["rocketSpecial"]);
        bool captiveBall_re_latch = b_blu && left2CaptiveBall_sw;
        bool captiveBall_re_trip = b_blu && right2CaptiveBall_sw;
        if (captiveBall_re_trip)
            reA["captiveBall"] = false;
        else if (captiveBall_re_latch)
            reA["captiveBall"] = true;

        // Section 1
        reA["SkylabBankReset"] = 
            (re["coin"] || re["skyLab"]) 
            && units["scoreMotor"] == 2;


        for (auto& pair : reA)
        {
            std::string key = pair.first;

            std::string out = pair.second.Print(re[key], change);
            if (out != "")
                std::cout << out << "\n";

        }

        for (auto& pair : unitsA)
        {
            std::string key = pair.first;

            std::string out = pair.second.Print(units[key], change);
            if (out != "")
                std::cout << out << "\n";
            out = pair.second.PrintEos(units[key], change);
            if (out != "")
                std::cout << out << "\n";

        }


        for (auto& pair : sol)
        {
            std::cout << pair.second;
        }

    }




}


