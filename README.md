<div id="top"></div>
<div align="center">
  <a href="https://github.com/Harshita-bali/rabies-vaccine-locator">
    <img src="https://github.com/Harshita-bali/rabies-vaccine-locator/assets/118011035/94704b8e-3fb5-4475-9ccb-21e6ea844f5d" alt="Logo" width="80" height="80">
  </a>

<h3 align="center">RABIES VACCINATION CENTER LOCATOR</h3>

  <p align="center">
    <br />
    <a href="https://github.com/Harshita-bali/rabies-vaccine-locator"><strong>Explore the docs »</strong></a>
    <br />
    <br />
    <a href="https://github.com/Harshita-bali/rabies-vaccine-locator">View Demo</a>
    ·
    <a href="https://github.com/Harshita-bali/rabies-vaccine-locator">Report Bug</a>
    ·
    <a href="https://github.com/Harshita-bali/rabies-vaccine-locator">Request Feature</a>
  </p>
  
</div>

## About The Project
<img src="https://github.com/Harshita-bali/rabies-vaccine-locator/assets/118011035/8bf4d768-37b9-47da-bb05-bed5dac9158d">
<div align="center" id="about-the-project">
 </div>
Rabies is a viral disease that affects the central nervous system and is primarily transmitted through the bite of an infected animal, most commonly dogs. When a rabid dog bites a human, the virus is introduced into the body through the saliva, traveling through the nerves to the brain, where it causes inflammation. Symptoms of rabies include fever, headache, excess salivation, muscle spasms, paralysis, and mental confusion. Without prompt and appropriate treatment, rabies is almost always fatal. Preventative measures, such as vaccinations for pets and immediate medical attention after a bite, are crucial in managing the risk of rabies.In India, rabies remains a significant public health concern, with the majority of cases resulting from dog bites. India accounts for nearly 36% of the world's rabies deaths, with thousands of fatalities each year. Therefore, we tried to work on this and make our own simple vaccine locator.Our project helps the user in locating the nearest vaccination center with their reviews about the sanitary condition and hygiene of the place, nearest metro station, and rating scale of 5 stars. In addition to that, it also provides regularly updated information on the availability of the slots regarding both dose 1 and dose 2. Locating the vaccination center will be based on the PIN code system and by direct selection through the map. The whole project will be GUI-based for convenient accessibility for the user.

### Built With
* [C++](https://isocpp.org/)
* [Computer Graphics(graphics.h)](https://developerinsider.co/graphics-graphics-h-c-programming/#:~:text=The%20graphics.,using%20initgraph%20method%20of%20graphics.)
* [Windows API](https://docs.microsoft.com/en-us/previous-versions/dd757161(v=vs.85))

### Data Set Used
* The data set used in this project has been retrieved from the following sites:
- https://www.google.com/maps
The initial Review data set is self-written and is random irrespective of the vaccination center.

### Test Bed
* CodeBlock 17.12
* Microsoft Excel 2019
<p align="right">(<a href="#top">↑</a>)</p>


## Getting Started
This is an example of how you may give instructions on setting up your project locally.
To get a local copy up and running follow these simple example steps.

### Prerequisites
In order to compile the following project in any IDE the basic requirement is a gcc 32 bit compiler and graphics.h library.
For smooth installation of the same refer to the given [link](https://www.youtube.com/watch?v=VEkAj-xVTKQ&t=361s)

Voilà, All Set.

<p align="right">(<a href="#top">↑</a>)</p>

## Project Design

 ### Class Diagram
 <img src="https://github.com/Harshita-bali/rabies-vaccine-locator/assets/118011035/11a3f947-a635-4892-bcf0-15739e225202" alt="">
 
 ### Some of the Project Features
 
 * Initial Review and corresponding rating list.
 ```sh
  vector<string> review_list={"Clean place", "Good staff and treatment", "Very capable authorities", "Cleanliness not up to mark", "Vaccination is done fast", "Okay type","Very long waiting time", "Nice and polite behaviour by staff", "Best in overall services", "Not the best but good", "Everything done quickly", "Very good hygiene followed", "Rude staff behaviour", "Very crowded place", "Lacks ventilation", "Good infrastructure", "Lacks basic amenities like drinking water", "Pleasant atmosphere", "Good supervision and management", "No holding area", "Poor parking facility", "Has a parking lot", "Overall good experience", "Whole place smelling bad"};
vector<int> rating_list={4,4,4,2,2,3,3,1,5,5,3,4,3,1,1,2,4,2,3,5,2,2,3,5,1};
  ```
 * Class to randomly assign a vaccine if it is PSP or TETNUS on the current date.
 ```sh
  class slots
{
public:
    string vaccine,date;
    int age_group,dose,avail_dose;
     slots()
     {
            time_t cur=time(0);
            localtime(&cur);
         date=((string)ctime(&cur)).substr(0,10);
         vaccine=(rand()%2==0)?"PSP":"TETNUS";
         age_group=rand()%2;
         dose=rand()%2;
         avail_dose=rand()%100;
     }
};
  ```
 * Calculating average rating and a function to add review and ratings to a center.
 ```sh
  void _avg()
    {   avg_r=0;
        for(auto i=rating.begin();i!=rating.end();i++)
            avg_r+=*i;
        avg_r/=rating.size();
    }
    void add_review(string rev,int rate)
    {
        review.push_back(rev);
        rating.push_back(rate);
        _avg();
    }
  ```
 * Assign random values to the inbuilt review data set for different hospitals. 
 ```sh
  centers(string name,string add,string _metro,string _pin,cord _xy={0,0})
    {
        _xy= cord(0,0);
        c_name=name;c_address=add;xy=_xy;
        metro=_metro;pin=_pin;
        avg_r=rand()%5+1;
        for(int i=0;i<(rand()%3)+1;i++)slot.push_back(slots());
        for(int i=0;i<(rand()%4)+1;i++)
            {
                int x=rand()%review_list.size();
                add_review(review_list[x],rating_list[x]);
            }
    }
  ```
 * User class implementation and checking for password and if a center is bookmarked by the user or not.
 ```sh
  user(string u,string p,string mob)
    {
        username=u;password=p;mob_n=mob;
    }
    string user_r()
    {
        return username;
    }
    bool pass_correct(string pass)
    {
        if(pass==password) return true;
        else return false;
    }
    bool is_bookmarked(string cname)
    {
        for(auto i=bookmarked.begin();i!=bookmarked.end();i++)
        {
            if(cname==*i)return true;
        }
        return false;
    }
  ```
* Function to ring a bell whenever the user signs in or logs out
 ```sh
 void program::notification(string s)
{
    if(1>0)
    {   mciSendString("open \"notf.mp3\" alias wav", NULL, 0, NULL);
        int size=s.size();
        mciSendString("play wav ",NULL,0,NULL);
        for(int i=0;i<30;i++)
        {   setbkcolor(BLACK);
        setcolor(WHITE);
        button(80,-30+i,100+7*size,-15+i,5,WHITE,BLACK);
        outtextxy(100,-30+i,(char*)s.c_str());
        delay(40);
        }
        delay(1500);
        for(int i=30;i>=0;i--)
        {
            setbkcolor(BLACK);
            setcolor(WHITE);
            button(80,-30+i,100+7*size,-14+i,5,WHITE,CYAN);
            button(80,-30+i,100+7*size,-15+i,5,WHITE,BLACK);
            outtextxy(100,-30+i,(char*)s.c_str());
            setcolor(CYAN);line(0,i-14,639,i-14);
        delay(40);
        }
        mciSendString("close wav",NULL,0,NULL);
    }
}
 ```

https://user-images.githubusercontent.com/79904688/149457045-fe4ca072-cf7c-45e1-a01e-b3983da1eb1f.mp4


<p align="right">(<a href="#top">↑</a>)</p>

## Result and Visualisation of the project

<div align="center
  * WELCOME SCREEN
 <img src="https://github.com/Harshita-bali/rabies-vaccine-locator/assets/118011035/e0ad600d-c88e-4cf7-a427-e9211fd2a04e="">
* LOGIN SCREEN

  
  <img src="static/output/2a.jpg" alt="">
  <img src="static/output/2b.jpg" alt="">
* SING UP SCREEN
  <img src="static/output/3.jpg" alt="">
* LOCATING CENTER BY PIN (after signing in)
  <img src="static/output/4a.jpg" alt="">
  <img src="static/output/4b.jpg" alt="">
* SELECTING FILTERS TO FIND REQUIRED VACCINE
  <img src="static/output/5a.jpg" alt="">
  <img src="static/output/5b.jpg" alt="">
* AVAILABLE SLOTS AND ADDING REVIEW
  <img src="static/output/6a.jpg" alt="">
  <img src="static/output/6b.jpg" alt="">
  <img src="static/output/6c.jpg" alt="">
* BOOKMARKING THE CENTER FOR FUTURE REFERENCE
  <img src="static/output/7.jpg" alt="">
* SELECTION THROUGH MAP
  <img src="static/output/8a.jpg" alt="">
  <img src="static/output/8b.jpg" alt="">
  <img src="static/output/8c.jpg" alt="">
  <img src="static/output/8d.jpg" alt="">
</div>
<p align="right">(<a href="#top">↑</a>)</p>

## Contact

HARSHITA BALI - [harshita13052005@gmail.com]

Project Link: [https://github.com/Harshita-bali/rabies-vaccine-locator](https://github.com/Harshita-bali/rabies-vaccine-locator)

