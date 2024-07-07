#include <bits/stdc++.h>
#include <graphics.h>
using namespace std;
float midx, midy;
vector<string> review_list = {"Clean place", "Good staff and treatment", "Very capable authorities", "Cleanliness not up to mark", "No social distancing followed", "Vaccination is done fast", "Okay type", "Very long waiting time", "Nice and polite behaviour by staff", "Best in overall services", "Not the best but good", "Everything done quickly", "Very good hygiene followed", "Rude staff behaviour", "Very crowded place", "Lacks ventilation", "Good infrastructure", "Lacks basic amenities like drinking water", "Pleasant atmosphere", "Good supervision and management", "No holding area", "Poor parking facility", "Has a parking lot", "Overall good experience", "Whole place smelling bad"};
vector<int> rating_list = {4, 4, 4, 2, 2, 3, 3, 1, 5, 5, 3, 4, 3, 1, 1, 2, 4, 2, 3, 5, 2, 2, 3, 5, 1};
class cord
{
public:
    float x, y;
    cord()
    {
    }
    cord(float a, float b)
    {
        x = a;
        y = b;
    }
};

class slots
{
public:
    string vaccine, date;
    int age_group, dose, avail_dose;
    slots()
    {
        time_t cur = time(0);
        localtime(&cur);
        date = ((string)ctime(&cur)).substr(0, 10);
        vaccine = (rand() % 2 == 0) ? "PEP" : "Tetanus";
        age_group = rand() % 2;
        dose = rand() % 2;
        avail_dose = rand() % 100;
    }
};
class centers
{
public:
    string c_name, c_address, metro, pin;
    vector<slots> slot;
    int avg_r;
    cord xy;
    vector<string> review;
    vector<int> rating;
    void _avg()
    {
        avg_r = 0;
        for (auto i = rating.begin(); i != rating.end(); i++)
            avg_r += *i;
        avg_r /= rating.size();
    }
    void add_review(string rev, int rate)
    {
        review.push_back(rev);
        rating.push_back(rate);
        _avg();
    }
    centers(string name, string add, string _metro, string _pin, cord _xy = {0, 0})
    {
        _xy = cord(0, 0);
        c_name = name;
        c_address = add;
        xy = _xy;
        metro = _metro;
        pin = _pin;
        avg_r = rand() % 5 + 1;
        for (int i = 0; i < (rand() % 3) + 1; i++)
            slot.push_back(slots());
        for (int i = 0; i < (rand() % 4) + 1; i++)
        {
            int x = rand() % review_list.size();
            add_review(review_list[x], rating_list[x]);
        }
    }
    centers(){};
};
vector<centers> centers_list;
class user
{
    string password, mob_n;

public:
    string username;
    vector<string> bookmarked;
    user(string u, string p, string mob)
    {
        username = u;
        password = p;
        mob_n = mob;
    }
    string user_r()
    {
        return username;
    }
    bool pass_correct(string pass)
    {
        if (pass == password)
            return true;
        else
            return false;
    }
    bool is_bookmarked(string cname)
    {
        for (auto i = bookmarked.begin(); i != bookmarked.end(); i++)
        {
            if (cname == *i)
                return true;
        }
        return false;
    }
    user() {}
};
class pins
{
public:
    string pin, district;
    vector<centers> center;
    void create_list()
    {
        for (auto i = centers_list.begin(); i != centers_list.end(); i++)
        {
            if (i->pin == this->pin)
                center.push_back(*i);
        }
    }
    pins(string p, string dname)
    {
        pin = p;
        district = dname;
        create_list();
    }
    pins() { pin = ""; };
};
vector<pins> pins_list;

class districts
{
public:
    int no_of_center;
    string district_name, state;
    vector<pins> pin;
    void add_pins()
    {
        for (auto i = pins_list.begin(); i != pins_list.end(); i++)
        {
            if (i->district == this->district_name)
            {
                pin.push_back(*i);
                no_of_center += i->center.size();
            }
        }
    }
    districts(string name, string s)
    {
        no_of_center = 0;
        state = s;
        district_name = name;
        add_pins();
    }
};
vector<districts> district_list;
class states
{
public:
    int no_of_districts;
    string s_name;
    vector<districts> district;
    void add_district()
    {
        for (auto i = district_list.begin(); i != district_list.end(); i++)
        {
            if (i->state == this->s_name)
            {
                district.push_back(*i);
            }
        }
    }
    states(string state)
    {
        s_name = state;
        add_district();
        no_of_districts = district.size();
    }
    states(){};
};
vector<states> state_list;
class bst_pin
{
public:
    pins pin;
    bst_pin *left, *right;

    // Default constructor.
    bst_pin();
    pins search(bst_pin *, string);
    // Parameterized constructor.
    bst_pin(pins p);

    bst_pin *insert(bst_pin *, pins p);

} *root = NULL;
bst_pin ::bst_pin() : pin(pins()), left(NULL), right(NULL)
{
}
bst_pin ::bst_pin(pins p)
{
    pin = p;
    left = right = NULL;
}

bst_pin *bst_pin ::insert(bst_pin *root, pins p)
{
    if (!root)
    {
        return new bst_pin(p);
    }
    if ((p.pin).compare(root->pin.pin) > 0)
    {

        root->right = insert(root->right, p);
    }
    else
    {
        root->left = insert(root->left, p);
    }
    return root;
}
pins bst_pin::search(bst_pin *root, string data)
{
    bst_pin *temp = new bst_pin;
    temp = root;
    while (temp != NULL)
    {
        if (temp->pin.pin == data)
        {
            return temp->pin;
        }
        else if (data.compare(temp->pin.pin) < 0)
            temp = temp->left;
        else
            temp = temp->right;
    }
    return pins();
}
class maps
{
public:
    map<int, states> state;
    maps()
    {
        state.insert({0, states("Maharashtra")});
        state.insert({1, states("Gujrat")});
        state.insert({2, states("Goa")});
        state.insert({3, states("Rajasthan")});
        state.insert({4, states("Karnataka")});
        state.insert({5, states("Delhi")});
        state.insert({6, states("Telangana")});
        state.insert({7, states("Tamil Nadu")});
        state.insert({8, states("Uttar Pradesh")});
        state.insert({9, states("West Bengal")});
        state.insert({10, states("Assam")});
        for (auto i = pins_list.begin(); i != pins_list.end(); i++)
        {
            root = root->insert(root, *i);
        }
    };
    states ret_state(int n)
    {
        return state.find(n)->second;
    }
};

class program
{
public:
    user logged_user;
    maps *mapping;
    vector<user> user_list;
    bool status, logged;
    void signup_scr(), login_scr(), login_scr_gfx(string, string, int), signup_scr_gfx(string, string, string, string, int);
    void init();
    void main_scr(), main_scr_gfx(int, string), center_scr_gfx(vector<centers>, string, vector<bool>, vector<bool>, int), border_gfx(), map_gfx();
    int main_scr_buttons(string &);
    void insert_data();
    void city(int, int);
    int sel_state();
    void notification(string);
    void button(int, int, int, int, int, int, int);
    void logo_name();
    void show_centers_by_pin(string &);
    void filter_list(vector<centers> &, vector<bool>);
    void show_center_details_gfx(centers &, int), show_center_details(centers &);
    void show_centers_by_map();
    void choose_district_gfx(states, int), centers_by_map(districts &);
    // public:
    program() {}
    program(string stat)
    {
        status = (stat == "run") ? true : false;
        logged = false;
        if (status)
            init();
        if (!status)
        {
            closegraph();
            exit(0);
        }
    }
};

int program ::sel_state()
{
    map_gfx();
    settextstyle(2, 0, 4);
    int a = 0;
    for (int i = 0; i < 11; i++)
    {
        if (i == a)
            city(i, 1);
        else
            city(i, 0);
    }
    while (1)
    {

        switch (getch())
        {
        case 75:
            if (a > 0)
                a--;
            else
                a = 10;
            for (int i = 0; i < 11; i++)
            {
                if (i == a)
                    city(i, 1);
                else
                    city(i, 0);
            }
            break;
        case 77:
            if (a < 10)
                a++;
            else
                a = 0;
            for (int j = 0; j < 11; j++)
            {
                if (j == a)
                    city(j, 1);
                else
                    city(j, 0);
            }
            break;
        case 13:
            return a;
        case 27:
            exit(0);
        }
    }
}
void program::city(int n, int value)
{
    setcolor(WHITE);
    setbkcolor(BLACK);
    settextstyle(2, 0, 4);
    setfillstyle(1, WHITE);
    if (value == 1)
    {
        setfillstyle(1, RED);
        setcolor(YELLOW);
    }
    switch (n)
    {
    case 0:
        fillellipse(225, 280, 3, 3);
        outtextxy(229, 270, (char *)"Maharashtra"); // Mumbai
        break;
    case 1:
        fillellipse(229, 233, 3, 3);
        outtextxy(232, 223, (char *)"Gujrat"); // Ahmedabad
        break;
    case 2:
        fillellipse(255, 344, 3, 3);
        outtextxy(259, 334, (char *)"Goa"); // Goa
        break;
    case 3:
        fillellipse(288, 171, 3, 3);
        outtextxy(292, 161, (char *)"Rajasthan"); // Jaipur
        break;
    case 4:
        fillellipse(304, 396, 3, 3);
        outtextxy(308, 385, (char *)"Karnataka"); // Bengaluru
        break;
    case 5:
        fillellipse(308, 129, 3, 3);
        outtextxy(312, 119, (char *)"Delhi"); // Delhi
        break;
    case 6:
        fillellipse(319, 319, 3, 3);
        outtextxy(323, 309, (char *)"Telangana"); // Hyderabad
        break;
    case 7:
        fillellipse(354, 399, 3, 3);
        outtextxy(358, 399, (char *)"Tamil Nadu"); // Chennai
        break;
    case 8:
        fillellipse(372, 171, 3, 3);
        outtextxy(376, 161, (char *)"Uttar Pradesh"); // Lucknow
        break;
    case 9:
        fillellipse(479, 225, 3, 3);
        outtextxy(483, 215, (char *)"West Bengal"); // Kolkata
        break;
    case 10:
        fillellipse(550, 160, 3, 3);
        outtextxy(554, 150, (char *)"Assam"); // Guwahati
        break;
    }
}
void program::map_gfx()
{
    cleardevice();
    border_gfx();
    int a[] = {251, 20, 257, 11, 260, 9, 275, 3, 277, 2, 299, 4, 305, 8, 305, 18, 316, 29, 341, 16, 353, 18, 357, 29, 361, 36, 346, 52, 348, 57, 353, 60, 353, 66, 345, 69, 343, 73, 343, 80, 341, 88, 346, 89, 349, 90, 351, 95, 357, 97, 361, 105, 368, 104, 377, 109, 371, 118, 368, 129, 372, 131, 385, 141, 419, 147, 425, 143, 433, 147, 441, 153, 458, 156, 469, 159, 490, 160, 494, 147, 491, 130, 502, 120, 513, 125, 509, 136, 511, 148, 514, 153, 526, 153, 532, 155, 547, 151, 553, 149, 553, 135, 543, 135, 543, 129, 540, 122, 548, 123, 551, 121, 576, 107, 583, 110, 586, 102, 596, 106, 607, 114, 602, 123, 614, 123,
               613, 141, 617, 145, 622, 152, 611, 148, 604, 153, 602, 168, 598, 183, 591, 188, 585, 186, 582, 199, 579, 211, 578, 217, 569, 217, 565, 201, 556, 208, 550, 203, 549, 192, 548, 190, 554, 187, 560, 172, 529, 175, 512, 171, 513, 164, 507, 162, 500, 157, 499, 163, 496, 164, 492, 171, 498, 174, 487, 182, 493, 195, 490, 213, 494, 232, 496, 236, 487, 238, 479, 234, 463, 248, 456, 269, 454, 274, 438, 278, 405, 318, 402, 327, 391, 329, 385, 339, 368, 339, 359, 345, 359, 361, 354, 377, 354, 396, 355, 412, 340, 436, 328, 436, 327, 447, 318, 464, 310, 477, 299, 474, 286, 441, 273, 412, 270, 408, 262, 357,
               244, 329, 242, 311, 235, 299, 225, 285, 224, 255, 221, 245, 218, 240, 217, 254, 214, 259, 197, 267, 187, 269, 179, 269, 171, 263, 162, 256, 157, 245, 155, 240, 156, 236, 150, 228, 169, 226, 181, 221, 170, 219, 150, 209, 144, 208, 138, 201, 144, 196, 153, 192, 161, 190, 173, 195, 187, 195, 196, 195, 192, 179, 185, 174, 191, 166, 180, 157, 187, 152, 195, 144, 200, 144, 203, 141, 208, 147, 207, 153, 213, 156, 220, 154, 220, 148, 232, 144, 235, 136, 246, 130, 252, 122, 257, 113, 270, 106, 273, 102, 273, 94, 288, 87, 285, 84, 276, 80, 270, 75, 267, 71, 265, 57, 263, 55, 263, 52, 273, 39, 268, 34, 266, 29,
               266, 28, 258, 24, 251, 20};
    setcolor(DARKGRAY);
    setbkcolor(BLACK);
    setfillstyle(10, DARKGRAY);
    fillpoly(188, a);
    setcolor(WHITE);
}
void program::border_gfx()
{
    floodfill(1, 1, 2);
    button(0, 0, getmaxx(), getmaxy(), 10, BLACK, CYAN);
    button(20, 20, 619, 459, 10, LIGHTCYAN, LIGHTCYAN);
}
void program::main_scr_gfx(int option = 1, string logged = "")
{
    settextstyle(-1, 0, 1);
    setcolor(LIGHTBLUE);
    if (this->logged)
    {
        setbkcolor(BLACK);
        button(460, 30, 610, 50, 5, YELLOW, BLACK);
        outtextxy(473, 32, (char *)(" Welcome, " + logged).c_str());
    }
    else
    {
        if (option == 1)
            button(460, 30, 530, 50, 5, LIGHTBLUE, BLACK);
        else
            button(460, 30, 530, 50, 5, LIGHTBLUE, LIGHTBLUE);
        if (option == 1)
        {
            setbkcolor(BLACK);
            setcolor(LIGHTCYAN);
        }
        else
        {
            setbkcolor(LIGHTBLUE);
            setcolor(WHITE);
        }
        outtextxy(473, 32, (char *)"LOG IN");

        if (option == 2)
            button(540, 30, 610, 50, 5, LIGHTBLUE, BLACK);
        else
            button(540, 30, 610, 50, 5, LIGHTBLUE, LIGHTBLUE);
        if (option == 2)
        {
            setbkcolor(BLACK);
            setcolor(LIGHTCYAN);
        }
        else
        {
            setbkcolor(LIGHTBLUE);
            setcolor(WHITE);
        }
        outtextxy(548, 32, (char *)"SIGN UP");
    }
    setcolor(BLACK);
    setbkcolor(LIGHTCYAN);
    setcolor(BLACK);
    outtextxy(150, 311, (char *)"PINCODE:");

    line(midx - 100, midy + 88, midx - 10, midy + 88);

    if (option == 3)
        button(319, 309, 390, 330, 5, LIGHTBLUE, BLACK);
    else
        button(319, 309, 390, 330, 5, LIGHTBLUE, LIGHTBLUE);
    if (option == 3)
    {
        setbkcolor(BLACK);
        setcolor(LIGHTCYAN);
    }
    else
    {
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
    }
    outtextxy(329, 311, (char *)"SUMBIT");

    if (option == 4)
        button(399, 309, 445, 330, 5, LIGHTBLUE, BLACK);
    else
        button(399, 309, 445, 330, 5, LIGHTBLUE, LIGHTBLUE);
    if (option == 4)
    {
        setbkcolor(BLACK);
        setcolor(LIGHTCYAN);
    }
    else
    {
        setbkcolor(LIGHTBLUE);
        setcolor(WHITE);
    }
    outtextxy(408, 311, (char *)"MAP");
}
void program::notification(string s)
{
    if (false)
    {
        mciSendString("open \"notf.mp3\" alias wav", NULL, 0, NULL);
        int size = s.size();
        mciSendString("play wav ", NULL, 0, NULL);
        for (int i = 0; i < 30; i++)
        {
            setbkcolor(BLACK);
            setcolor(WHITE);
            button(80, -30 + i, 100 + 7 * size, -15 + i, 5, WHITE, BLACK);
            outtextxy(100, -30 + i, (char *)s.c_str());
            delay(40);
        }
        delay(1500);
        for (int i = 30; i >= 0; i--)
        {
            setbkcolor(BLACK);
            setcolor(WHITE);
            button(80, -30 + i, 100 + 7 * size, -14 + i, 5, WHITE, CYAN);
            button(80, -30 + i, 100 + 7 * size, -15 + i, 5, WHITE, BLACK);
            outtextxy(100, -30 + i, (char *)s.c_str());
            setcolor(CYAN);
            line(0, i - 14, 639, i - 14);
            delay(40);
        }
        mciSendString("close wav", NULL, 0, NULL);
    }
}
int program::main_scr_buttons(string &pincode)
{
    int flag = 1;
    if (logged)
        flag = 3;
    main_scr_gfx(flag, logged_user.username);
    while (1)
    {
        settextstyle(8, 0, 1);
        setbkcolor(LIGHTCYAN);
        setcolor(BLACK);
        outtextxy(midx - 87, midy + 70, (char *)"      ");
        outtextxy(midx - 87, midy + 70, (char *)pincode.c_str());
        switch (getch())
        {
        case 72:
            if (logged)
                flag = 3;
            else
                flag = 1;
            main_scr_gfx(flag, logged_user.username);
            break;
        case 80:
            flag = 3;
            main_scr_gfx(flag, logged_user.username);
            break;
        case 75:
            if (flag == 2 || flag == 1)
                flag = 1;
            else if (flag == 3 || flag == 4)
                flag = 3;
            main_scr_gfx(flag, logged_user.username);
            break;
        case 77:
            if (flag == 1)
                flag = 2;
            else if (flag == 3)
                flag = 4;
            main_scr_gfx(flag, logged_user.username);
            break;
        case 13:
            if (flag == 3 && pincode.size() == 6)
                return flag;
            if (flag != 3)
                return flag;
            break;
        case 27:
            if (logged)
            {
                logged_user = user();
                logged = false;
                main_scr();
                return 0;
            }
            else
                return -1;
        case 48:
            if (pincode.size() < 6)
            {
                pincode.append("0");
                flag = 3;
                main_scr_gfx(flag, logged_user.username);
            }
            break;
        case 49:
            if (pincode.size() < 6)
            {
                pincode.append("1");
                flag = 3;
                main_scr_gfx(flag, logged_user.username);
            }
            break;
        case 50:
            if (pincode.size() < 6)
            {
                pincode.append("2");
                flag = 3;
                main_scr_gfx(flag, logged_user.username);
            }
            break;
        case 51:
            if (pincode.size() < 6)
            {
                pincode.append("3");
                flag = 3;
                main_scr_gfx(flag, logged_user.username);
            }
            break;
        case 52:
            if (pincode.size() < 6)
            {
                pincode.append("4");
                flag = 3;
                main_scr_gfx(flag, logged_user.username);
            }
            break;
        case 53:
            if (pincode.size() < 6)
            {
                pincode.append("5");
                flag = 3;
                main_scr_gfx(flag, logged_user.username);
            }
            break;
        case 54:
            if (pincode.size() < 6)
            {
                pincode.append("6");
                flag = 3;
                main_scr_gfx(flag, logged_user.username);
            }
            break;
        case 55:
            if (pincode.size() < 6)
            {
                pincode.append("7");
                flag = 3;
                main_scr_gfx(flag, logged_user.username);
            }
            break;
        case 56:
            if (pincode.size() < 6)
            {
                pincode.append("8");
                flag = 3;
                main_scr_gfx(flag, logged_user.username);
            }
            break;
        case 57:
            if (pincode.size() < 6)
            {
                pincode.append("9");
                flag = 3;
                main_scr_gfx(flag, logged_user.username);
            }
            break;
        case 8:
            if (pincode.size() > 0)
                pincode.pop_back();
            break;
        default:
            continue;
        };

        // notification();
    }
}
void program::button(int x1, int y1, int x2, int y2, int r, int color, int f_color)
{
    setcolor(f_color);
    setfillstyle(1, f_color);
    int arr[] = {x1, y1 + r, x1 + r, y1, x2 - r, y1, x2, y1 + r, x2, y2 - r, x2 - r, y2, x1 + r, y2, x1, y2 - r, x1, y1 + r};

    fillpoly(8, arr);
    setcolor(f_color);
    fillellipse(x1 + r, y1 + r, r, r);
    fillellipse(x2 - r + 1, y1 + r, r, r);
    fillellipse(x2 - r + 1, y2 - r + 1, r, r);
    fillellipse(x1 + r, y2 - r + 1, r, r);
    setcolor(color);
}
void program::logo_name()
{
    setcolor(BLACK);
    setbkcolor(LIGHTCYAN);
    settextstyle(10, 0, 4);
    outtextxy(midx - 185, midy - 50, (char *)"RABIES VACCINE LOCATOR");
}
void program::filter_list(vector<centers> &c_list, vector<bool> filter)
{
    if (filter == (vector<bool>){false, false, false, false})
        return;
    for (auto i = c_list.begin(); i != c_list.end(); i++)
    {
        bool flag1 = true, flag2 = true;
        if (filter[0] || filter[1])
        {
            if (filter[0] && !filter[1])
            {
                for (auto j = i->slot.begin(); j != i->slot.end(); j++)
                {
                    if (j->age_group != 0)
                        i->slot.erase(j--);
                }
            }
            if (filter[1] && !filter[0])
            {
                for (auto j = i->slot.begin(); j != i->slot.end(); j++)
                {
                    if (j->age_group != 1)
                        i->slot.erase(j--);
                }
            }
        }
        if (filter[2] || filter[3])
        {
            if (filter[2] && !filter[3])
            { 
                for (auto j = i->slot.begin(); j != i->slot.end(); j++)
                {
                    if (j->vaccine != "PEP")
                        i->slot.erase(j--);
                }
            }
            if (filter[3] && !filter[2])
            {
                for (auto j = i->slot.begin(); j != i->slot.end(); j++)
                {
                    if (j->vaccine != "Tetanus")
                        i->slot.erase(j--);
                }
            }
        }
        if (i->slot.empty())
            c_list.erase(i--);
    }
}
void program::center_scr_gfx(vector<centers> c_list, string district, vector<bool> filter, vector<bool> p_filter, int flag = 1)
{
    cleardevice();
    filter_list(c_list, p_filter);
    border_gfx();
    setcolor(BLACK);
    settextstyle(-1, 0, 1);
    if (flag == 2)
    {
        button(109, 101, 201, 124, 5, WHITE, BLUE);
        button(219, 101, 311, 124, 5, WHITE, BLUE);
        button(329, 101, 421, 124, 5, WHITE, BLUE);
        button(439, 101, 516, 124, 5, WHITE, BLUE);
    }
    else
    {
        button(109, 101, 201, 124, 5, WHITE, WHITE);
        button(219, 101, 311, 124, 5, WHITE, WHITE);
        button(329, 101, 421, 124, 5, WHITE, WHITE);
        button(439, 101, 516, 124, 5, WHITE, WHITE);
    }
    if (filter[0])
    {
        button(110, 102, 200, 123, 5, WHITE, BLUE);
        setbkcolor(BLUE);
    }
    else
    {
        button(110, 102, 200, 123, 5, BLUE, WHITE);
        setbkcolor(WHITE);
    }
    outtextxy(125, 105, (char *)"Minors");
    if (filter[1])
    {
        button(220, 102, 310, 123, 5, WHITE, BLUE);
        setbkcolor(BLUE);
    }
    else
    {
        button(220, 102, 310, 123, 5, BLUE, WHITE);
        setbkcolor(WHITE);
    }
    outtextxy(230, 105, (char *)"Adults");
    if (filter[2])
    {
        button(330, 102, 420, 123, 5, WHITE, BLUE);
        setbkcolor(BLUE);
    }
    else
    {
        button(330, 102, 420, 123, 5, BLUE, WHITE);
        setbkcolor(WHITE);
    }
    outtextxy(343, 105, (char *)"PEP");
    if (filter[3])
    {
        button(440, 102, 515, 123, 5, WHITE, BLUE);
        setbkcolor(BLUE);
    }
    else
    {
        button(440, 102, 515, 123, 5, BLUE, WHITE);
        setbkcolor(WHITE);
    }
    outtextxy(450, 105, (char *)" Tetanus ");
    setbkcolor(BLACK);
    settextstyle(8, 0, 1);
    if (flag == 1)
        button(midx - 151, 34, midx + 181, 66, 5, BLUE, LIGHTRED);
    else
        button(midx - 151, 34, midx + 181, 66, 5, BLUE, BLACK);
    button(midx - 150, 35, midx + 180, 65, 5, BLUE, BLACK);

    if (flag == 3)
        button(44, 139, getmaxx() - 44, getmaxy() - 29, 10, BLUE, GREEN);
    else
        button(44, 139, getmaxx() - 44, getmaxy() - 29, 10, BLUE, LIGHTGREEN);
    button(45, 140, getmaxx() - 45, getmaxy() - 30, 10, BLUE, LIGHTGREEN);
    setbkcolor(LIGHTGREEN);
    setcolor(BLACK);
    if (c_list.size() == 0)
    {
        outtextxy(midx - 140, 270, (char *)"No Slots Available Right Now");
        getch();
        return;
    }
    int size = c_list.size();
    int index = 0, y = 150;
    if (flag > 3)
        index = flag - 4;
    if (!district.empty())
    {
        setcolor(YELLOW);
        setbkcolor(BLACK);
        outtextxy(midx - 100, 41, (char *)c_list[index].pin.c_str());
        outtextxy(midx + 10, 41, (char *)district.c_str());
    }
    for (int i = index; i <= index + 4 && i < size && (y < 420); i++)
    {
        setbkcolor(WHITE);
        settextstyle(9, 0, 1);
        if (i == index)
            button(49, y - 1, getmaxx() - 49, y + 61, 5, BLACK, BLACK);
        else
            button(49, y - 1, getmaxx() - 49, y + 61, 5, BLACK, WHITE);
        button(50, y, getmaxx() - 50, y + 60, 5, BLACK, WHITE);
        outtextxy(55, y + 2, (char *)c_list[i].c_name.c_str());
        settextstyle(-1, 0, 1);
        outtextxy(55, y + 22, (char *)c_list[i].c_address.c_str());
        outtextxy(55, y + 42, (char *)("Nearest Metro Station : " + c_list[i].metro).c_str());
        outtextxy(getmaxx() - 180, y + 42, (char *)"Review :");
        for (int k = 1; k <= 5; k++)
        {
            if (k <= c_list[i].avg_r)
            {
                setcolor(BLACK);
                setfillstyle(1, YELLOW);
            }
            else
            {
                setcolor(BLACK);
                setfillstyle(1, WHITE);
            }
            fillellipse(getmaxx() - 135 + 15 * k, y + 50, 5, 5);
        }
        y += 70;
    }
}
void program::show_center_details_gfx(centers &c, int flag = 1)
{
    cleardevice();
    border_gfx();
    button(midx - 150, 35, midx + 150, 65, 5, BLUE, BLACK);
    setcolor(YELLOW);
    setbkcolor(BLACK);
    settextstyle(-1, 0, 1);
    outtextxy(midx - 85, 41, (char *)c.c_name.c_str());
    {
        int arr[] = {getmaxx() - 70, 19, getmaxx() - 50, 19, getmaxx() - 50, 60, getmaxx() - 60, 50, getmaxx() - 70, 60, getmaxx() - 70, 19};
        if (logged_user.is_bookmarked(c.c_name))
        {
            setcolor(DARKGRAY);
            setfillstyle(1, BLACK);
        }
        else
        {
            setcolor(BLACK);
            setfillstyle(1, WHITE);
        }
        if (flag == 1)
            setcolor(LIGHTRED);
        fillpoly(5, arr);
    }
    setcolor(BLACK);
    setbkcolor(LIGHTCYAN);
    settextstyle(-1, 0, 1);
    if (flag == 2)
        line(150, 134, getmaxx() - 120, 134);
    outtextxy(45, 112, (char *)"Write a Review =");
    line(150, 130, getmaxx() - 120, 130);
    button(getmaxx() - 105, 110, getmaxx() - 40, 130, 5, YELLOW, BLACK);
    setbkcolor(BLACK);
    outtextxy(getmaxx() - 97, 112, (char *)"SUBMIT");
    button(45, 140, getmaxx() - 45, midy + 30, 10, BLUE, LIGHTGREEN);
    setbkcolor(WHITE);
    settextstyle(11, 0, 1);
    button(60, 170, 160, 210, 10, BLACK, WHITE);
    outtextxy(80, 182, (char *)"PEP");
    button(60, 220, 160, 260, 10, BLACK, WHITE);
    outtextxy(80, 232, (char *)"  Tetanus ");
    int x = 180;
    for (auto i = c.slot.begin(); i != c.slot.end(); i++)
    {
        int y = 0;
        setbkcolor(BLUE);
        settextstyle(11, 0, 1);
        button(x, 147, x + 72, 168, 5, WHITE, BLUE);
        outtextxy(x + 3, 150, (char *)i->date.c_str());
        setcolor(BLACK);
        setbkcolor(LIGHTGREEN);
        settextstyle(3, 0, 1);
        if (i->vaccine == "Tetanus")
            y = 50;
        outtextxy(x + 22, 178 + y, (char *)to_string(i->avail_dose).c_str());
        settextstyle(2, 0, 4);
        outtextxy(x + 19, 198 + y, (char *)("Doses Left"));
        x += 90;
    }
    if (flag >= 3)
        button(44, midy + 39, getmaxx() - 44, getmaxy() - 29, 10, BLUE, GREEN);
    else
        button(44, midy + 39, getmaxx() - 44, getmaxy() - 29, 10, BLUE, LIGHTGREEN);
    button(45, midy + 40, getmaxx() - 45, getmaxy() - 30, 10, BLUE, LIGHTGREEN);
    setbkcolor(LIGHTGREEN);
    settextstyle(11, 0, 1);
    outtextxy(midx - 30, midy + 45, (char *)"Reviews");
    int index = 0, y = midy + 80;
    if (flag > 3)
        index = flag - 4;
    for (int i = index; i <= index + 5 && i < c.review.size() && (y < 420); i++)
    {
        setbkcolor(WHITE);
        settextstyle(-1, 0, 1);
        if (flag >= 3 && i == index)
            button(49, y - 1, getmaxx() - 49, y + 21, 5, BLACK, BLACK);
        else
            button(49, y - 1, getmaxx() - 49, y + 21, 5, BLACK, WHITE);
        button(50, y, getmaxx() - 50, y + 20, 5, BLACK, WHITE);
        outtextxy(55, y + 2, (char *)c.review[i].c_str());
        settextstyle(-1, 0, 1);
        for (int k = 1; k <= 5; k++)
        {
            if (k <= c.rating[i])
            {
                setcolor(BLACK);
                setfillstyle(1, YELLOW);
            }
            else
            {
                setcolor(BLACK);
                setfillstyle(1, WHITE);
            }
            fillellipse(getmaxx() - 135 + 15 * k, y + 10, 5, 5);
        }
        y += 25;
    }
}

void program::show_center_details(centers &c)
{
    int flag = 1;
    int stars = 1;
    int index = 1;
    string review = "";
    show_center_details_gfx(c);
    while (1)
    {
        for (int k = 1; k <= 5; k++)
        {
            if (k <= stars)
            {
                setcolor(BLACK);
                setfillstyle(1, YELLOW);
            }
            else
            {
                setcolor(BLACK);
                setfillstyle(1, WHITE);
            }
            fillellipse(midx - 50 + 15 * k, 100, 5, 5);
        }
        char ch = getch();
        switch (ch)
        {
        case 72:
            if (flag == 3)
            {
                if (index > 1)
                    index = index - 1;
                show_center_details_gfx(c, flag + index);
            }
            break;
        case 80:
            if (flag == 3)
            {
                if (index < c.review.size())
                    index = index + 1;
                show_center_details_gfx(c, flag + index);
            }
            break;
        case 75:
            if (flag == 2 && stars > 1)
                stars--;
            break;
        case 77:
            if (flag == 2 && stars < 5)
                stars++;
            break;
        case 13:
            if (flag == 1)
            {
                if (logged)
                {
                    if (logged_user.is_bookmarked(c.c_name))
                    {
                        logged_user.bookmarked.erase(find(logged_user.bookmarked.begin(), logged_user.bookmarked.end(), c.c_name));
                    }
                    else
                    {
                        logged_user.bookmarked.push_back(c.c_name);
                    }
                }
                else
                {
                    notification("You need to login in-order to bookmark.");
                    notification("Transferring to Login Screen");
                    login_scr();
                }
            }
            else if (flag == 2)
            {
                if (review.size() == 0)
                    review = "<empty>";
                c.add_review(review, stars);
                for (auto i = centers_list.begin(); i != centers_list.end(); i++)
                {
                    if (i->c_name == c.c_name)
                        *i = c;
                }
                review = "";
                stars = 1;
            }
            show_center_details_gfx(c);
            break;
        case 27:
            return;
        case 9:
            flag = flag % 3 + 1;
            show_center_details_gfx(c, flag);
            break;
        case 8:
            if (review.size() > 0)
                review.pop_back();
            break;
        default:
            if ((isalnum(ch) || ch == 32) && review.size() < 40 && ch != 7)
            {
                flag = 2;
                review += ch;
            }
        };
        settextstyle(-1, 0, 1);
        setbkcolor(LIGHTCYAN);
        setcolor(BLACK);
        outtextxy(152, 112, (char *)"                                                                                                                          ");
        outtextxy(152, 112, (char *)review.c_str());
    }
}
void program::show_centers_by_pin(string &pincode)
{
    pins p = root->search(root, pincode);
    vector<centers> center_at_pin;
    string district = "";
    bool found = false;
    int flag = 2, f_flag = 0, index = 1;
    if (p.pin != "")
    {
        center_at_pin = p.center;
        found = true;
        district = p.district;
    }
    vector<bool> filter = {false, false, false, false};
    center_scr_gfx(center_at_pin, district, filter, filter, flag);
    while (found)
    {
        vector<bool> temp = filter;
        settextstyle(8, 0, 1);
        setbkcolor(BLACK);
        setcolor(YELLOW);
        outtextxy(midx - 100, 41, (char *)"      ");
        outtextxy(midx - 100, 41, (char *)pincode.c_str());

        switch (getch())
        {
        case 72:
            if (flag == 3)
            {
                if (index > 1)
                    index = index - 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag + index);
                break;
            }
        case 80:
            if (flag == 3)
            {
                if (index < center_at_pin.size())
                    index = index + 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag + index);
                break;
            }
        case 9:
        {
            flag = flag % 3 + 1;
            center_scr_gfx(center_at_pin, district, filter, filter, flag);
            break;
        }
        case 75:
            if (flag == 2)
            {
                f_flag = (f_flag <= 1) ? 4 : (f_flag - 1);
                temp[f_flag - 1] = true;
                center_scr_gfx(center_at_pin, district, temp, filter, flag);
                break;
            }
            else
                continue;
        case 77:
            if (flag == 2)
            {
                f_flag = f_flag % 4 + 1;
                temp[f_flag - 1] = true;
                center_scr_gfx(center_at_pin, district, temp, filter, flag);
                break;
            }
            else
                continue;
        case 13:
            if (flag == 1)
                show_centers_by_pin(pincode);
            if ((flag == 3) && (pincode.size() == 6))
            {
                show_center_details(center_at_pin[index - 1]);
                for (auto i = pins_list.begin(); i != pins_list.end(); i++)
                {
                    if (i->pin == pincode)
                    {
                        i->center = center_at_pin;
                        break;
                    }
                }
                center_scr_gfx(center_at_pin, district, temp, filter, flag);
            }
            break;
        case 32:
            if (flag == 2)
            {
                filter[f_flag - 1] = !filter[f_flag - 1];
                // refresh screen
                center_scr_gfx(center_at_pin, district, filter, filter, flag);
            }
            break;
        case 27:
            return;
        case 48:
            if (pincode.size() < 6)
            {
                pincode.append("0");
                flag = 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag);
            }
            break;
        case 49:
            if (pincode.size() < 6)
            {
                pincode.append("1");
                flag = 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag);
            }
            break;
        case 50:
            if (pincode.size() < 6)
            {
                pincode.append("2");
                flag = 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag);
            }
            break;
        case 51:
            if (pincode.size() < 6)
            {
                pincode.append("3");
                flag = 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag);
            }
            break;
        case 52:
            if (pincode.size() < 6)
            {
                pincode.append("4");
                flag = 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag);
            }
            break;
        case 53:
            if (pincode.size() < 6)
            {
                pincode.append("5");
                flag = 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag);
            }
            break;
        case 54:
            if (pincode.size() < 6)
            {
                pincode.append("6");
                flag = 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag);
            }
            break;
        case 55:
            if (pincode.size() < 6)
            {
                pincode.append("7");
                flag = 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag);
            }
            break;
        case 56:
            if (pincode.size() < 6)
            {
                pincode.append("8");
                flag = 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag);
            }
            break;
        case 57:
            if (pincode.size() < 6)
            {
                pincode.append("9");
                flag = 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag);
            }
            break;
        case 8:
            if (pincode.size() > 0)
                pincode.pop_back();
            flag = 1;
            break;
        default:
            continue;
        };
        // notification();
    }
}
void program::choose_district_gfx(states s, int flag = 0)
{
    cleardevice();
    border_gfx();
    button(midx - 150, 35, midx + 150, 65, 5, YELLOW, BLACK);
    setbkcolor(BLACK);
    settextstyle(3, 0, 2);
    outtextxy(midx - 4 * s.s_name.size(), 37, (char *)s.s_name.c_str());
    setbkcolor(LIGHTCYAN);
    setcolor(BLACK);
    outtextxy(midx - 50, 80, (char *)"Select District :");
    int x = 100, y = 150, j = 0, t = 120;
    for (auto i = s.district.begin(); i != s.district.end(); i++, j++)
    {
        settextstyle(-1, 0, 1);
        button(x, y, x + 90, y + 25, 5, BLUE, WHITE);
        setbkcolor(WHITE);
        if (j == flag)
        {
            button(x + 1, y + 1, x + 90, y + 25, 5, WHITE, BLUE);
            setbkcolor(BLUE);
        }
        else
        {
            button(x + 1, y + 1, x + 90, y + 25, 5, BLUE, WHITE);
            setbkcolor(WHITE);
        }

        outtextxy(x + 10, y + 5, (char *)i->district_name.c_str());
        x += t;
        y += 35;
        if (y >= 290)
            t = -120;
    }
}
void program::centers_by_map(districts &d)
{
    vector<centers> center_at_pin;
    string district = d.district_name;
    bool found = false;
    int flag = 1, f_flag = 0, index = 1;
    for (auto i = d.pin.begin(); i != d.pin.end(); i++)
    {
        center_at_pin.insert(center_at_pin.end(), i->center.begin(), i->center.end());
    }
    if (center_at_pin.size() > 0)
        found = true;
    vector<bool> filter = {false, false, false, false};
    center_scr_gfx(center_at_pin, district, filter, filter, flag + 1);
    while (found)
    {
        vector<bool> temp = filter;
        settextstyle(8, 0, 1);
        setbkcolor(BLACK);
        setcolor(YELLOW);

        switch (getch())
        {
        case 72:
            flag = 2;
            if (index > 1)
            {
                index = index - 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag + index + 1);
            }

            break;
        case 80:
            flag = 2;
            if (index < center_at_pin.size())
            {
                index = index + 1;
                center_scr_gfx(center_at_pin, district, filter, filter, flag + index + 1);
            }

            break;
        case 9:
        {
            flag = flag % 2 + 1;
            center_scr_gfx(center_at_pin, district, filter, filter, flag + 1);
            break;
        }
        case 75:
            if (flag == 1)
            {
                f_flag = (f_flag <= 1) ? 4 : (f_flag - 1);
                temp[f_flag - 1] = true;
                center_scr_gfx(center_at_pin, district, temp, filter, flag + 1);
                break;
            }
            break;
        case 77:
            if (flag == 1)
            {
                f_flag = f_flag % 4 + 1;
                temp[f_flag - 1] = true;
                center_scr_gfx(center_at_pin, district, temp, filter, flag + 1);
                break;
            }
            break;
        case 13:
            if (flag == 2)
            {
                show_center_details(center_at_pin[index - 1]);
                for (auto i = pins_list.begin(); i != pins_list.end(); i++)
                {
                    if (i->pin == center_at_pin[index - 1].pin)
                    {
                        i->center = center_at_pin;
                        break;
                    }
                }
                center_scr_gfx(center_at_pin, district, temp, filter, flag + 1);
            }
            break;
        case 32:
            if (flag == 1)
            {
                filter[f_flag - 1] = !filter[f_flag - 1];
                // refresh screen
                center_scr_gfx(center_at_pin, district, filter, filter, flag + 1);
            }
            break;
        case 27:
            return;
        default:
            continue;
        };
        // notification();
    }
}
void program::show_centers_by_map()
{
    states state = mapping->ret_state(sel_state());
    choose_district_gfx(state);
    int n = state.no_of_districts, flag = 0;
    while (1)
    {
        switch (getch())
        {
        case 72:
        case 75:
            flag = (flag <= 0) ? n - 1 : (flag - 1);
            break;
        case 80:
        case 77:
            flag = (flag + 1) % n;
            break;
        case 27:
            return;
        case 13:
            centers_by_map(state.district[flag]);
            break;
        default:
            continue;
        };
        choose_district_gfx(state, flag);
    }
}
void program::main_scr()
{

    string pincode = "";

    while (status)
    {
        cleardevice();
        border_gfx();
        logo_name();
        int button = main_scr_buttons(pincode);
        switch (button)
        {
        case -1:
            status = false;
            return;
        case 1:
            login_scr();
            break;
        case 2:
            signup_scr();
            break;
        case 3:
            show_centers_by_pin(pincode);
            break;
        case 4:
            show_centers_by_map();
            break;
        default:
            break;
        };
    }
}
void program::login_scr_gfx(string u = "", string p = "", int flag = 1)
{
    cleardevice();
    border_gfx();
    string temp = "";
    for (int i = 0; i < p.size(); i++)
        temp += "* ";
    if (temp.size() == 0)
        temp = "Password";
    if (u.size() == 0)
        u = "Username";
    button(330, 20, 619, 459, 10, LIGHTGRAY, LIGHTCYAN);
    button(20, 20, 350, 459, 10, YELLOW, BLACK);
    for (int i = 0; i < 8; i++)
    {
        setcolor(i + 8);
        arc(20, 459, -1, 87, 80 - 10 * i);
        arc(350, 20, 181, 271, 80 - 10 * i);
    }
    setcolor(WHITE);
    settextstyle(8, 0, 3);
    setbkcolor(BLACK);
    outtextxy(100, 200, (char *)"WELCOME BACK");
    settextstyle(11, 0, 1);
    outtextxy(100, 250, (char *)"Please Enter Your Credentials");
    settextstyle(-1, 0, 1);
    setcolor(BLACK);
    setbkcolor(WHITE);
    if (flag == 1)
        button(379, 199, 591, 231, 10, DARKGRAY, DARKGRAY);
    else
        button(379, 199, 591, 231, 10, DARKGRAY, WHITE);
    button(380, 200, 590, 230, 10, DARKGRAY, WHITE);
    {
        int arr[] = {387, 214, 394, 214, 394, 220, 387, 220, 387, 214};
        setfillstyle(1, BLACK);
        setcolor(BLACK);
        fillpoly(4, arr);
        fillellipse(391, 210, 3, 3);
    }
    setcolor(DARKGRAY);
    outtextxy(400, 207, (char *)u.c_str());
    if (flag == 2)
        button(379, 244, 591, 276, 10, DARKGRAY, DARKGRAY);
    else
        button(379, 244, 591, 276, 10, DARKGRAY, WHITE);
    button(380, 245, 590, 275, 10, DARKGRAY, WHITE);
    {
        int arr[] = {387, 259, 394, 259, 394, 265, 387, 265, 387, 259};
        setfillstyle(1, BLACK);
        setcolor(BLACK);
        fillpoly(4, arr);
        arc(391, 259, 0, 180, 3);
    }
    setcolor(DARKGRAY);
    outtextxy(400, 252, (char *)temp.c_str());
    if (flag == 3)
        button(534, 289, 601, 311, 5, BLACK, DARKGRAY);
    else
        button(534, 289, 601, 311, 5, BLACK, WHITE);
    button(535, 290, 600, 310, 5, BLACK, WHITE);
    setbkcolor(WHITE);
    settextstyle(-1, 0, 1);
    outtextxy(547, 292, (char *)"LOGIN");
    setbkcolor(LIGHTCYAN);
    setcolor(DARKGRAY);
    outtextxy(385, 422, (char *)"Don't have an account?");
    setcolor(BLACK);
    if (flag == 4)
        setcolor(LIGHTRED);
    outtextxy(530, 422, (char *)"Sign Up");
    line(530, 440, 580, 440);
    if (flag == 4)
        line(530, 442, 580, 442);
}
void program::login_scr()
{
    string username = "", password = "";
    int flag = 1;
    login_scr_gfx();
    string error;
    while (1)
    {
        char ch = getch();
        switch (ch)
        {
        case 72:
            flag = (flag <= 1) ? 4 : (flag - 1);
            login_scr_gfx(username, password, flag);
            break;
        case 80:
            flag = flag % 4 + 1;
            login_scr_gfx(username, password, flag);
            break;
        case 75:
            break;
        case 77:
            break;
        case 13:
            if (flag == 4)
            {
                signup_scr();
                return;
            }
            else if (flag == 1)
            {
                if (username.size() == 0)
                {
                    error = "Empty User-name . Try again ";
                    notification(error);
                }
                else
                    flag++;
            }
            else if (flag == 2)
            {
                if (password.size() == 0)
                {
                    error = "Please Enter Password . Try again ";
                    notification(error);
                }
                else
                    flag++;
            }
            if (flag == 3)
            {
                bool exist = false;
                for (auto i = user_list.begin(); i != user_list.end() && (exist == false); i++)
                {
                    if (i->username == username)
                    {
                        exist = true;
                        if (i->pass_correct(password))
                        {
                            logged_user = *i;
                            logged = true;
                            error = "Successfully Logged In.";
                            notification(error);
                        }
                        else
                        {
                            error = "Incorrect Password. Try again.";
                            notification(error);
                        }
                    }
                }
                if (!exist)
                {
                    error = "User Not found . Want to Sign Up?";
                    notification(error);
                    flag = 4;
                }
                else
                {
                    main_scr();
                    return;
                }
            }
            login_scr_gfx(username, password, flag);
            break;
        case 27:
            return;
        case 9:
            flag = flag % 4 + 1;
            login_scr_gfx(username, password, flag);
            break;
        case 8:
            if (flag == 1 && username.size() > 0)
                username.pop_back();
            else if (flag == 2 && password.size() > 0)
                password.pop_back();
            login_scr_gfx(username, password, flag);
            break;
        default:
            if ((isalnum(ch) || ch == 32) && ch != 7 && flag < 3)
            {
                if (flag == 1 && username.size() <= 15)
                    username += ch;
                else if (flag == 2 && password.size() <= 15)
                    password += ch;
                login_scr_gfx(username, password, flag);
            }
        };
    }
}
void program::signup_scr_gfx(string u = "", string p = "", string r = "", string m = "", int flag = 1)
{
    cleardevice();
    border_gfx();
    string temp = "";

    if (u.size() == 0)
        u = "Username";
    if (m.size() == 0)
        m = "Mobile Number";
    button(20, 20, 350, 459, 10, YELLOW, LIGHTCYAN);
    button(300, 20, 619, 459, 10, LIGHTGRAY, BLACK);
    for (int i = 0; i < 8; i++)
    {
        setcolor(i + 8);
        arc(300, 459, -1, 87, 80 - 10 * i);
        arc(619, 20, 181, 271, 80 - 10 * i);
    }
    setcolor(WHITE);
    settextstyle(8, 0, 3);
    setbkcolor(BLACK);
    outtextxy(320, 150, (char *)"A Few Steps Away");
    settextstyle(8, 0, 2);
    outtextxy(360, 200, (char *)"From Getting Yourself");
    settextstyle(8, 0, 4);
    outtextxy(350, 250, (char *)"VACCINATED");
    settextstyle(10, 0, 2);
    setbkcolor(LIGHTCYAN);
    setcolor(BLACK);
    outtextxy(80, 115, (char *)"Create Account");
    settextstyle(-1, 0, 1);
    setcolor(BLACK);
    setbkcolor(WHITE);
    if (flag == 1)
        button(49, 154, 271, 186, 10, DARKGRAY, DARKGRAY);
    else
        button(49, 154, 271, 186, 10, DARKGRAY, WHITE);
    button(50, 155, 270, 185, 10, DARKGRAY, WHITE);
    {
        int arr[] = {57, 169, 64, 169, 64, 175, 57, 175, 57, 169};
        setfillstyle(1, BLACK);
        setcolor(BLACK);
        fillpoly(4, arr);
        fillellipse(61, 165, 3, 3);
    }
    setcolor(DARKGRAY);
    outtextxy(70, 162, (char *)u.c_str());
    if (flag == 2)
        button(49, 199, 271, 231, 10, DARKGRAY, DARKGRAY);
    else
        button(49, 199, 271, 231, 10, DARKGRAY, WHITE);
    button(50, 200, 270, 230, 10, DARKGRAY, WHITE);
    {
        int arr[] = {57, 214, 64, 214, 64, 220, 57, 220, 57, 214};
        setfillstyle(1, BLACK);
        setcolor(BLACK);
        fillpoly(4, arr);
        arc(61, 214, 0, 180, 3);
    }
    setcolor(DARKGRAY);
    for (int i = 0; i < p.size(); i++)
        temp += "* ";
    if (temp.size() == 0)
        temp = "Password";
    outtextxy(70, 207, (char *)temp.c_str());
    if (flag == 3)
        button(49, 244, 271, 276, 10, DARKGRAY, DARKGRAY);
    else
        button(49, 244, 271, 276, 10, DARKGRAY, WHITE);
    button(50, 245, 270, 275, 10, DARKGRAY, WHITE);
    {
        int arr[] = {57, 259, 64, 259, 64, 265, 57, 265, 57, 259};
        setfillstyle(1, BLACK);
        setcolor(BLACK);
        fillpoly(4, arr);
        arc(61, 259, 0, 180, 3);
    }
    setcolor(DARKGRAY);
    temp.clear();
    for (int i = 0; i < r.size(); i++)
        temp += "* ";
    if (temp.size() == 0)
        temp = "Re-Password";
    outtextxy(70, 252, (char *)temp.c_str());
    if (flag == 4)
        button(49, 289, 271, 321, 10, DARKGRAY, DARKGRAY);
    else
        button(49, 289, 271, 321, 10, DARKGRAY, WHITE);
    button(50, 290, 270, 320, 10, DARKGRAY, WHITE);
    {
        int arr[] = {64, 303, 58, 308, 59, 309, 64, 302};
        setfillstyle(1, BLACK);
        setcolor(BLACK);
        fillpoly(4, arr);
        fillellipse(63, 302, 2, 3);
        fillellipse(57, 309, 2, 3);
    }
    setcolor(DARKGRAY);
    outtextxy(70, 297, (char *)m.c_str());
    if (flag == 5)
        button(204, 334, 271, 356, 5, BLACK, DARKGRAY);
    else
        button(204, 334, 271, 356, 5, BLACK, WHITE);
    button(205, 335, 270, 355, 5, BLACK, WHITE);
    setbkcolor(WHITE);
    settextstyle(-1, 0, 1);
    outtextxy(212, 337, (char *)"SIGN UP");
    setcolor(DARKGRAY);
    setbkcolor(LIGHTCYAN);
    outtextxy(55, 422, (char *)"Already have an account?");
    setcolor(BLACK);
    setcolor(BLACK);
    if (flag == 6)
    {
        setcolor(LIGHTRED);
        line(218, 442, 258, 442);
    }
    outtextxy(220, 422, (char *)"Log in");
    line(218, 440, 258, 440);
}
void program::signup_scr()
{
    string username = "", password = "", repass = "", mobile = "";
    string error;
    int flag = 1;
    signup_scr_gfx();
    while (1)
    {
        char ch = getch();
        switch (ch)
        {
        case 72:
            flag = (flag <= 1) ? 6 : (flag - 1);
            signup_scr_gfx(username, password, repass, mobile, flag);
            break;
        case 80:
            flag = flag % 6 + 1;
            signup_scr_gfx(username, password, repass, mobile, flag);
            break;
        case 75:
            break;
        case 77:
            break;
        case 13:
            if (flag == 6)
            {
                login_scr();
                return;
            }
            else if (flag == 1)
            {
                if (username.size() == 0)
                {
                    error = "Empty User-name . Try again ";
                    notification(error);
                }
                else
                    flag++;
            }
            else if (flag == 2)
            {
                if (password.size() == 0)
                {
                    error = "Please Enter Password . Try again ";
                    notification(error);
                }
                else
                    flag++;
            }
            else if (flag == 3)
            {
                if (repass.size() == 0)
                {
                    error = "Please Re-Enter Password . Try again ";
                    notification(error);
                }
                else
                    flag++;
            }
            else if (flag == 4)
            {
                if (mobile.size() == 0)
                {
                    error = "Please Enter Valid Mobile Number.";
                    notification(error);
                }
                else
                    flag++;
            }
            if (flag == 5)
            {
                bool already = false;
                if (password != repass)
                {
                    error = "Password Don't Match. Try Again.";
                    notification(error);
                }
                else
                {
                    for (auto i = user_list.begin(); i != user_list.end(); i++)
                    {
                        if (i->username == username)
                        {
                            already = true;
                        }
                        break;
                    }
                    if (already)
                    {
                        error = "You Already Have an account try logging in.";
                        flag = 6;
                        notification(error);
                    }
                    else
                    {
                        user_list.push_back(user(username, password, mobile));
                        error = "Account Successfully created. Transferring to Login Screen.";
                        notification(error);
                        delay(500);
                        login_scr();
                        return;
                    }
                }
            }

            signup_scr_gfx(username, password, repass, mobile, flag);
            break;
        case 27:
            return;
        case 9:
            flag = flag % 6 + 1;
            signup_scr_gfx(username, password, repass, mobile, flag);
            break;
        case 8:
            if (flag == 1 && username.size() > 0)
                username.pop_back();
            else if (flag == 2 && password.size() > 0)
                password.pop_back();
            else if (flag == 3 && repass.size() > 0)
                repass.pop_back();
            else if (flag == 4 && mobile.size() > 0)
                mobile.pop_back();
            signup_scr_gfx(username, password, repass, mobile, flag);
            break;
        default:
            if ((isalnum(ch) || ch == 32) && ch != 7 && flag <= 4)
            {
                if ((flag == 4) && (isdigit(ch)) && mobile.size() < 10)
                    mobile += ch;
                if (flag == 1 && username.size() <= 15)
                    username += ch;
                else if (flag == 2 && password.size() <= 15)
                    password += ch;
                else if (flag == 3 && repass.size() <= 15)
                    repass += ch;
                signup_scr_gfx(username, password, repass, mobile, flag);
            }
        };
    }
}

void program::init()
{

    insert_data();
    user_list.push_back(user("admin", "admin", "191"));
    int gdriver = DETECT, gmode, errorcode;
    initgraph(&gdriver, &gmode, NULL);
    midx = getmaxx() / 2;
    midy = getmaxy() / 2;
    main_scr();
}
void program::insert_data()
{
    cout << "refreshing data.......";
    centers_list.push_back(centers("Aruna Asaf Ali Govt Hospital", "5, Rajpur Rd, Police Lines, Civil Lines, New Delhi", "Tis Hazari", "110054"));
    centers_list.push_back(centers("Sant Parmanand Hospital", "18, Sham Nath Marg, Civil Lines, New Delhi", "Civil Lines", "110054"));
    centers_list.push_back(centers("St. Stephen's Hospital", "St. Stephen's Hospital Marg, Tis Hazari, New Delhi", "Tis Hazari", "110054"));
    centers_list.push_back(centers("Burari Hospital", "Burari Rd, Kaushik Enclave, Shankarpura, Burari", "Majlish Park", "110084"));
    centers_list.push_back(centers("Guru Gobind Singh Hospital (GGSH)", "Sant Nagar Marg, A-2 Block, Virendar Nagar, Block B, West Sant Nagar, Burari", "Majlish Park", "110084"));
    centers_list.push_back(centers("City Child & Family Care Hospital", "Sant Nagar Marg, Laxmi Vihar, Extension Colony, Burari", "Shiv Vihar", "110084"));
    centers_list.push_back(centers("Delhi Heart & Lung Institute", "Rolex, 3, Panchkuian Marg, Type 4, Block B, Aram Bagh, Paharganj", "R.K. Ashram Marg", "110055"));
    centers_list.push_back(centers("Northern Railway Central Hospital", "Basant Lane, Aram Bagh, Connaught Place, Paharganj", "Rajiv Chowk", "110055"));
    centers_list.push_back(centers("Sunderlal Jain Hospital", "10393, Sardar Thana Rd, Motia Khan, Sadar Bazaar", "Jhandewalan", "110055"));
    centers_list.push_back(centers("BLK Super Speciality Hospital", "Pusa Rd, Radha Soami Satsang, Rajendra Place", "Rajendra Place", "110005"));
    centers_list.push_back(centers("Shree Jeewan Hospital", "67/1, New Rohtak Rd, Block 67, Karol Bagh", "Pratap Nagar", "110005"));
    centers_list.push_back(centers("Dr. N.C. Joshi Memorial Hospital", "Joshi Path, near Ajmal Khan Park, Block 63, Karol Bagh", "Pulbangash", "110005"));
    centers_list.push_back(centers("Lal Bahadur Shastri Hospital", "384, Indra Camp, near Lal Bahadur Shashtri hospital emergency gate, Khichripur, Kalyan Puri", "East Vinod Nagar- Mayur Vihar-II", "110091"));
    centers_list.push_back(centers("DGD Trilokpuri", "F299, Subhash Market, Block 5, Part 1, Trilokpuri, New Delhi, Delhi 110091", "Trilokpuri- Sanjay Lake", "110091"));
    centers_list.push_back(centers("Central Govt Health Scheme - DIspensary", "1st St, Pratap Nagar, Mayur Vihar, Delhi, 110091", "Mayur Vihar Pkt-1", "110091"));
    centers_list.push_back(centers("Max Super Speciality Hospital, Patparganj", "108A, I.P.Extension, Patparganj, Delhi, 110092", "IP Extension", "110092"));
    centers_list.push_back(centers("Manglam Hospital", "Block B, Block D, West Vinod Nagar, New Delhi, Delhi 110092", "Mandawali- West Vinod Nagar", "110092"));
    centers_list.push_back(centers("Pushpanjali Medical Centre", " A-14/15, Vikas Marg Ext, Pushpanjali, Karkardooma, Anand Vihar, New Delhi, Delhi 110092", "Anand Vihar Metro Station", "110092"));
    centers_list.push_back(centers("Goyal Hospital & Urology Centre", "E-4/8, Krishna Nagar, near Lajpat Rai Chowk, New Delhi, Delhi 110051", "East Azad Nagar", "110051"));
    centers_list.push_back(centers("Khandelwal Hospital And Urology Center", "B-16, Main Road, East Krishna Nagar, East Krishna Nagar, New Delhi, Delhi 110051", "Krishna Nagar", "110051"));
    centers_list.push_back(centers("Singhani Multi-speciality Hospital", "15, Gagan Vihar, Krishna Nagar, Delhi, 110051", "Preet Vihar", "110051"));
    centers_list.push_back(centers("Dharamshila Narayana Superspeciality Hospital", "Metro Station, Dharamshila marg, Vasundhara Enclave Near Ashok Nagar, Dallupura, New Delhi, Delhi 110096", "New Ashok Nagar", "110096"));
    centers_list.push_back(centers("GEO hospital", "Shital Vihar, Khora Colony, Sector 62A, Noida, Uttar Pradesh 110096", "Sector 62 Noida", "110096"));
    centers_list.push_back(centers("Max Hospital", "19, Noida Rd, Block B, Sector - 19 A, Sector - 106, Noida, Delhi ", "East Vinod Nagar- Mayur Vihar-II", "110096"));
    centers_list.push_back(centers("Charak Palika Hospital", "C 7 Ln, Moti Bagh 1, Block F, Moti Bagh, New Delhi, Delhi 110021", "Sir M Vishveshwaraiah Moti Bagh", "110021"));
    centers_list.push_back(centers("Primus Super Speciality Hospital", "Chandragupta Marg, Opp Russian Embassy, Chanakyapuri", "Durgabai Deshmukh South Campus", "110021"));
    centers_list.push_back(centers("Sadhu Vaswani Mission Medical Centre", "4, 27, Rd Number 4, Sector 4, Shanti Niketan", "Sir M Vishveshwaraiah Moti Bagh", "110021"));
    centers_list.push_back(centers("Dr. Ram Manohar Lohia Hospital", "Baba Kharak Singh Rd, near Gurudwara Bangla Sahib, Ram Manohar Lohia Hospital", "R.K. Ashram Marg", "110001"));
    centers_list.push_back(centers("Sir Ganga Ram Hospital", "Sir Ganga Ram Hospital Marg, Old Rajinder Nagar, New Rajinder Nagar", "Karol Bagh", "110001"));
    centers_list.push_back(centers("G.b. Pant Hospital", "Supreme Court, No. 1, Sikandra Rd, Bhagwan Das Lane, Mandi House", "Mandi House", "110001"));
    centers_list.push_back(centers("Lok Nayak Hospital", "Jawaharlal Nehru Marg, near Delhi Gate, New Delhi, Delhi 110002", "Central", "110002"));
    centers_list.push_back(centers("Kasturba Hospital", " Gate No.1, New Delhi, Delhi 110006", "Jama Masjid", "110002"));
    centers_list.push_back(centers("Mrs. Girdhar Lal Maternity Hospital", "Jawaharlal Nehru Marg, Kamla Market, Ajmeri Gate, New Delhi, Delhi 110002", "New Delhi", "110002"));
    centers_list.push_back(centers("CGHS Dispensary", "Dr Zakir Hussain Marg, Pandara Park, India Gate, New Delhi, Delhi 110003", "Khan Market", "110003"));
    centers_list.push_back(centers("Palika Maternity Hospital", "Block 11, Lodhi Colony, near Khanna Market, New Delhi, Delhi 110003", "Jorbagh", "110003"));
    centers_list.push_back(centers("ECHS Polyclinic Lodhi Road", "Bhishma Pitamah Marg, near Sai Baba Mandir, Meharchand Market, Pragati Vihar", "JLN Stadium", "110003"));
    centers_list.push_back(centers("CGHS Dispensary Wellness Centre, Hauz Khas", "near Dr Dang lab, Safdarjung Development Area, Hauz Khas", "Hauz Khas", "110016"));
    centers_list.push_back(centers("Sitaram Bhartia Institute of Science and Research", "B-16, Qutab Institutional Area Block B Rd, NRPC Colony, Block B", "R.K. Puram", "110016"));
    centers_list.push_back(centers("Medeor Hospital Qutab Institutional Area", "B-33-34, Block B, Qutab Institutional Area, New Delhi, Delhi 110016", "IIT - Bureau of Indian Standards", "110016"));
    centers_list.push_back(centers("AIIMS Hospital", "Ansari Nagar East, Gautam Nagar, Ansari Nagar East, New Delhi, Delhi 110029", "AIIMS", "110029"));
    centers_list.push_back(centers("Safdarjung Hospital", "Ansari Nagar East, near to AIIMS Metro Station, New Delhi, Delhi 110029", "AIIMS", "110029"));
    centers_list.push_back(centers("Sukhmani Hospital", "126A, opposite Rajasthan Vidyut Niwas, B-7, Block B 7, Arjun Nagar, Safdarjung Enclave", "Green Park", "110029"));
    centers_list.push_back(centers("Fortis C-Doc Hospital", "B 16, Chirag Enclave Rd, Chirag Enclave, Greater Kailash, New Delhi, Delhi 110048", "Nehru Enclave", "110048"));
    centers_list.push_back(centers("SCI International Hospital", "4, Hansraj Gupta Rd, Greater Kailash-1, M Block, Greater Kailash I, Greater Kailash", "Greater Kailash", "110048"));
    centers_list.push_back(centers("Talwar Medical Centre", "M-139, CR Park Road, Greater Kailash II, New Delhi, Delhi 110048", "Greater Kailash", "110048"));
    centers_list.push_back(centers("PSRI Hospital", "Press Enclave Marg, J Pocket, Phase II, Sheikh Sarai, New Delhi, Delhi 110017", "Chirag Delhi", "110017"));
    centers_list.push_back(centers("Pt. Madan Mohan Malaviya Hospital", "Khirki Extension, Malviya Nagar, New Delhi, Delhi 110017", "Panchsheel Park", "110017"));
    centers_list.push_back(centers("Max Super Speciality Hospital, Saket", "1 2, Press Enclave Marg, Saket Institutional Area, Saket", "Malviya Nagar", "110017"));
    centers_list.push_back(centers("Metro Multispeciality Hospital", "L-94, near Punjab National Bank, Sector 11, Noida, Uttar Pradesh 201301", "Wave City Center Noida", "201301"));
    centers_list.push_back(centers("FORTIS HOSPITAL PVT", "Rasoolpur Nawada Industrial Area Sector 62 NOIDA, Gautam Buddha Nagar, Uttar Pradesh, 201301", "Noida Sector 18", "201301"));
    centers_list.push_back(centers("APOLLO HOSPITALS PVT", "Block E, Sector 51, Noida, Uttar Pradesh 201301", "Sector 52 Noida", "201301"));
    centers_list.push_back(centers("SHARDA HOSPITAL G NOIDA", "Plot No.32-34 Knowledge Park-3 Greater Noida, Gautam Buddha Nagar, Uttar Pradesh", "Noida Sector 147", "201310"));
    centers_list.push_back(centers("Yatharth Super Speciality Hospital, Greater Noida", "Omega-I, Plot No 32, MG Rd, Greater Noida, Uttar Pradesh", "Knowledge park 2", "201310"));
    centers_list.push_back(centers("Shri Krishna Life Line Hospital", "NH-22 D, Sector-TAU, Swarn Nagari, Sector 31, Greater Noida, Uttar Pradesh", "Alpha 1", "201310"));
    pins_list.push_back(pins("110054", "Central Delhi"));
    pins_list.push_back(pins("110084", "Central Delhi"));
    pins_list.push_back(pins("110055", "Central Delhi"));
    pins_list.push_back(pins("110005", "Central Delhi"));
    pins_list.push_back(pins("110091", "East Delhi"));
    pins_list.push_back(pins("110092", "East Delhi"));
    pins_list.push_back(pins("110051", "East Delhi"));
    pins_list.push_back(pins("110096", "East Delhi"));
    pins_list.push_back(pins("110021", "New Delhi"));
    pins_list.push_back(pins("110001", "New Delhi"));
    pins_list.push_back(pins("110002", "New Delhi"));
    pins_list.push_back(pins("110003", "New Delhi"));
    pins_list.push_back(pins("110016", "South Delhi"));
    pins_list.push_back(pins("110029", "South Delhi"));
    pins_list.push_back(pins("110048", "South Delhi"));
    pins_list.push_back(pins("110017", "South Delhi"));
    pins_list.push_back(pins("201301", "Noida"));
    pins_list.push_back(pins("201310", "Noida"));
    district_list.push_back(districts("Central Delhi", "Delhi"));
    district_list.push_back(districts("East Delhi", "Delhi"));
    district_list.push_back(districts("New Delhi", "Delhi"));
    district_list.push_back(districts("South Delhi", "Delhi"));
    district_list.push_back(districts("Noida", "Uttar Pradesh"));
    state_list.push_back(states("Delhi"));
    state_list.push_back(states("Uttar Pradesh"));
    mapping = new maps();
    cout << endl
         << "updated data......";
}
int main()
{

    srand(time(0));
    int gdriver = DETECT, gmode, errorcode;
    initgraph(&gdriver, &gmode, NULL);
    midx = getmaxx() / 2;
    midy = getmaxy() / 2;
    program rabies_locator = program("run");
    getch();
    return 0;
}
