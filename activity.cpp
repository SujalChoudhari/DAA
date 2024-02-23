#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
class Activity
{
public:
    std::string name;
    int start;
    int finish;

    Activity(std::string name, int start, int finish) : name(name), start(start), finish(finish)
    {
    }

    static std::vector<Activity> Selection(Activity *activities, std::vector<Activity> selected)
    {
        std::sort(activities, activities + 6, [](const Activity &a, const Activity &b)
                  { return a.finish < b.finish; });

        selected.push_back(activities[0]);
        int n = 6;
        for (int j = 0, i = 1; i < n; i++)
        {
            if (activities[i].start >= activities[j].finish)
            {
                selected.push_back(activities[i]);
                j = i;
            }
        }

        return selected;
    }
};

Activity jobs[6] = {
    Activity("a1", 5, 9),
    Activity("a2", 1, 2),
    Activity("a3", 3, 4),
    Activity("a4", 0, 6),
    Activity("a5", 5, 7),
    Activity("a6", 8, 9)};

int main()
{
    std::vector<Activity> selected = std::vector<Activity>();
    selected = Activity::Selection(jobs, selected);
    std::cout << "\n";
    for (Activity a : selected)
    {
        std::cout << "--> | " << a.name << " | ";
    }
    std::cout << "\n";
    return 0;
}