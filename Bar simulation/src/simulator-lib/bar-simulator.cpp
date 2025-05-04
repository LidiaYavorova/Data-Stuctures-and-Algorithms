#include "bar-simulator.h"

///
/// @brief Simulate the student bar problem
///
/// @param input
///   The stream, which contains the simulation commands
/// @param output
///   The stream, where the steps of simulation have to be printed.
///
const int MAX_UNSIGNED = 4294967295;
template <typename T>
class DList {
private:
    struct Node
    {
        T data;
        Node* next = nullptr, * prev = nullptr;
        Node(const T& val = T(), Node* next = nullptr, Node* prev = nullptr) : data(val), next(next), prev(prev) {}
    };
    Node sentinel;
    int count = 0;

public:

    class iterator
    {
        friend class DList;
        Node* current;
        iterator(Node* current = nullptr) : current(current) {};
    public:
        iterator& operator++()
        {
            current = current->next;
            return (*this);
        }
        iterator& operator++(int)
        {
            iterator res(*this);
            ++(*this);
            return res;
        }
        iterator& operator--()
        {
            current = current->prev;
            return (*this);
        }
        iterator& operator--(int)
        {
            iterator res(*this);
            --(*this);
            return res;
        }

        T& operator*()
        {
            return current->data;
        }

        T* operator->()
        {
            return &(current->data);
        }

        bool operator==(const iterator& it) const
        {
            return current == it.current;
        }
        bool operator!=(const iterator& it) const
        {
            return !(current == it.current);
        }

    };
    DList()
    {
        sentinel.next = sentinel.prev = &sentinel;
    }
    DList(const DList& other) : DList()
    {
        Node* iter = &sentinel;
        Node* curr = other.sentinel.next;
        while (curr != &other.sentinel) {
            iter->next = new Node(curr->data, iter);
            iter = iter->next;
            curr = curr->next;
        }
        count = other.count;
        sentinel.prev = count ? iter : &sentinel;
        iter->next = &sentinel;
    }
    DList& operator=(const DList& other)
    {
        if (this != &other)
        {
            clear();
            Node* iter = &sentinel;
            Node* curr = other.sentinel.next;
            while (curr != &other.sentinel) {
                iter->next = new Node(curr->data, iter);
                iter = iter->next;
                curr = curr->next;
            }
            size = other.size;
            sentinel.prev = size ? iter : &sentinel;
            iter->next = &sentinel;
        }
        return *this;
    }
    ~DList()
    {
        clear();
    }

    void clear()
    {
        while (!empty())
        {
            pop_front();
        }
    }


    int size() const
    {
        return count;
    }

    bool empty() const
    {
        return count == 0;
    }
    iterator begin()
    {
        return iterator(sentinel.next);
    }

    iterator end()
    {
        return iterator(&sentinel);
    }

    iterator insert(iterator it, const T& el)
    {
        Node* newNode = new Node{ el };
        newNode->next = it.current;
        newNode->prev = it.current->prev;
        newNode->next->prev = newNode;
        newNode->prev->next = newNode;
        ++count;
        return iterator(newNode);
    }

    void push_front(const T& el)
    {
        insert(begin(), el);
    }

    void push_back(const T& el) //O(1)
    {
        insert(&sentinel, el);
    }

    iterator erase(iterator it)
    {

        it.current->prev->next = it.current->next;
        it.current->next->prev = it.current->prev;
        iterator result(it.current->next);
        delete it.current;
        --count;
        return result;


    }
    void pop_front()
    {
        erase(sentinel.prev);

    }

    void pop_back()
    {
        erase(begin());
    }

    void merge(DList& head2) {
        // If the current list is empty, simply take the contents of the second list
        if (!sentinel.next) {
            sentinel.next = head2.sentinel.next;
            sentinel.prev = head2.sentinel.prev;
            count = head2.count;

            // Reset the second list
            head2.sentinel.next = head2.sentinel.prev = nullptr;
            head2.count = 0;

            return;
        }

        // If the second list is empty, nothing needs to be done
        if (!head2.sentinel.next) {
            return;
        }

        // Connect the last node of the first list to the head of the second list
        sentinel.prev->next = head2.sentinel.next;
        head2.sentinel.next->prev = sentinel.prev;

        // Update the last node of the current list to be the last node of the second list
        sentinel.prev = head2.sentinel.prev;
        head2.sentinel.prev->next = &sentinel;

        // Update the count of elements in the current list
        count += head2.count;

        // Reset the second list
        head2.sentinel.next = head2.sentinel.prev = nullptr;
        head2.count = 0;
    }
};

struct Group {
    Specialty major;
    DList<Student> students;
};


bool canJoinGroup(const Student& student, const Group& group, int groupCapacity)
{
    return ((student.spec == group.major) && group.students.size() < groupCapacity);
}

Student readStudent(Student& student, std::istream& input)
{
    if (input >> student.facultyNumber >> student.minutes)
    {
        if (student.facultyNumber > 999999999 || student.minutes == MAX_UNSIGNED)
        {
            throw std::runtime_error("Faculty number or minutes is invalid");
        }
        std::string major;
        input >> major;
        if (major == "Fraud")
        {
            student.spec = Specialty::Fraud;
        }
        else if (major == "International")
        {
            input >> major;
            if (major == "Schemes")
            {
                student.spec = Specialty::InternationalSchemes;
            }
        }
        else if (major == "Creative")
        {
            input >> major;
            if (major == "Nihilism")
            {
                student.spec = Specialty::CreativeNihilism;
            }
        }
        else if (major == "Subjective")
        {
            input >> major;
            if (major == "Researches")
            {
                student.spec = Specialty::SubjectiveResearches;
            }
        }
        else if (major == "File")
        {
            input >> major;
            if (major == "Analizis")
            {
                student.spec = Specialty::FileAnalizis;
            }
        }
        else if (major == "Micromanagement")
        {
            student.spec = Specialty::Micromanagement;
        }
        else if (major == "Applied")
        {
            input >> major;
            if (major == "Materialization")
            {
                student.spec = Specialty::AppliedMaterialization;
            }
        }
        else if (major == "Subjectivistics")
        {
            student.spec = Specialty::Subjectivistics;
        }
        else if (major == "Magnetism")
        {
            input >> major;
            if (major == "and")
            {
                input >> major;
                if (major == "Clearing")
                {
                    student.spec = Specialty::MagnetismandClearing;
                }
            }
        }
        else
        {
            throw std::runtime_error("Invalid specialty");
        }
        input >> student.enthusiasm;
        if (student.enthusiasm == MAX_UNSIGNED)
        {
            throw std::runtime_error("Invalid enthusiasm.");
        }
        return student;
    }
    else
    {
        throw std::runtime_error("Students are less than indicated number in advance");
    }
}

void simulate_bar(std::istream& input, std::ostream& output)
{
    int clubCapacity, groupCapacity, studentsCount;
    input >> clubCapacity >> groupCapacity >> studentsCount;
    if (clubCapacity == 0)
    {
        if (studentsCount > 0)
        {
            throw std::runtime_error("Invalid input data");
        }
        return;
    }

    DList<Group> groups;
    DList<Student> studentsInside;
    Student student;
    int currentMinute = 0;
    bool isStudentDistributedInAGroup = true;
    bool isPersonsMinuteSameAsTheCurrentMinute = true;

    //The simulation stops when all the students have been read from the input and there is no one outside and inside the bar
    while (!groups.empty() || !studentsInside.empty() || studentsCount)
    {
        //If there is a person who hasn't been distributed or if not all of the students are currently being read
        if (studentsCount > 0 || !isStudentDistributedInAGroup)
        {
            //If last person was distributed, then we can continue to read a new student
            if (isStudentDistributedInAGroup)
            {
                student = readStudent(student, input);
                studentsCount--;
                isStudentDistributedInAGroup = false;
            }

            //Check for sorted input
            if (student.minutes < currentMinute)
            {
                throw std::runtime_error("Not a valid minute");
            }

            if (student.minutes == currentMinute)
            {
                isPersonsMinuteSameAsTheCurrentMinute = true;
                bool joinedGroup = false;

                //Attempt to join an existing group
                DList<Group>::iterator groupIt = groups.begin();
                while (groupIt != groups.end())
                {
                    if (canJoinGroup(student, *groupIt, groupCapacity))
                    {
                        groupIt->students.push_back(student);
                        joinedGroup = true;
                        break;
                    }
                    ++groupIt;

                }

                //If couldn't join an existing group, create a new one
                if (!joinedGroup)
                {
                    Group newGroup;
                    newGroup.major = student.spec;
                    newGroup.students.push_back(student);
                    groups.push_back(newGroup);

                }
                isStudentDistributedInAGroup = true;

            }
            else
            {
                isStudentDistributedInAGroup = false;
                isPersonsMinuteSameAsTheCurrentMinute = false;
            }
        }
        else
        {
            isPersonsMinuteSameAsTheCurrentMinute = false;
        }

        //If there is more than one person coming at the same minute, we do not increment the time until we are sure we have distributed all of them
        //Because enthusiasm of people changes with the time, we are careful when we update the time
        if (!isPersonsMinuteSameAsTheCurrentMinute)
        {
            ++currentMinute;
            DList<Student>::iterator insideIt = studentsInside.begin();
            while (insideIt != studentsInside.end())
            {

                insideIt->enthusiasm -= 1;
                // Assuming students spend 1 minute inside

                if (insideIt->enthusiasm <= 0)
                {
                    output << currentMinute << " " << insideIt->facultyNumber << " exit\n";
                    insideIt = studentsInside.erase(insideIt);
                    clubCapacity++;
                }
                else
                {
                    ++insideIt;
                }
            }

        }

        //Accepting new groups in the club if it is possible
        DList<Group>::iterator groupIt = groups.begin();
        while (groupIt != groups.end())
        {
            if (groupIt->students.size() <= clubCapacity)
            {
                DList<Student>::iterator studentIt = groupIt->students.begin();
                for (studentIt; studentIt != groupIt->students.end(); ++studentIt)
                {
                    output << currentMinute << " " << studentIt->facultyNumber << " enter\n";
                    clubCapacity--;
                }
                //Merging the group with the list of students inside
                studentsInside.merge(groupIt->students);
                // Remove the group if all students have entered
                groupIt = groups.erase(groupIt);
            }
            else
            {
                ++groupIt;  // Move to the next group
            }
        }
    }
}
