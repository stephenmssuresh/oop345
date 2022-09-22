# Workshop 5: Functions and Error Handling

In this workshop, you code a function object and a lambda expression, and handle exceptions.

The goal is to define a family of central units that manage and handle jobs. For example, your computer's Central Processing Unit (CPU) is a central unit that hosts and coordinates individual processing units (ALU, Control Unit, etc.) to handle processing a computational job.

Here, we will create a CPU-like central unit that hosts and manages different microprocessors (i.e. its individual processing units) to process jobs and handle errors that come up when processing those jobs. Your code for this central unit should, however, work with any type of individual unit, not just microprocessors (e.g. the central unit can be a load balancer or routing server and the individual units can be regular servers)

## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- design and code a templated class that allocates and deallocates dynamic memory
- design and code a function object
- design and code a lambda expression
- code a member function that receives the address of a callback function to execute 
- throw exceptions of different types
- distinguish exception types from one another

## Submission Policy

The workshop is divided into two coding parts and one non-coding part:

- *Part 1*: worth 0% of the workshop's total mark, is optional and designed to assist you in completing the second part.
- *Part 2*: worth 100% of the workshop's total mark, is due on **Sunday at 23:59:59** of the week of your scheduled lab.  Submissions of *Part 2* that do not contain the *reflection* are not considered valid submissions and are ignored.
- *reflection*: non-coding part, to be submitted together with *Part 2*. The reflection does not have marks associated to it, but can incur a **penalty of max 40% of the whole workshop's mark** if your professor deems it insufficient (you make your marks from the code, but you can lose some on the reflection).

The workshop should contain ***only work done by you this term*** or provided by your professor.  Work done in another term (by you or somebody else), or work done by somebody else and not **clearly identified/cited** is considered plagiarism, in violation of the Academic Integrity Policy.

Every file that you submit must contain (as a comment) at the top **your name**, **your Seneca email**, **Seneca Student ID** and the **date** when you completed the work.

- If the file contains only your work, or work provided to you by your professor, add the following message as a comment at the top of the file:

    > I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
- If the file contains work that is not yours (you found it online or somebody provided it to you), **write exactly which parts of the assignment are given to you as help, who gave it to you, or which source you received it from.**  By doing this you will only lose the mark for the parts you got help for, and the person helping you will be cleared of any wrongdoing.


## Compiling and Testing Your Program

All your code should be compiled using this command on `matrix`:

```bash
/usr/local/gcc/10.2.0/bin/g++ -Wall -std=c++17 -g -o ws file1.cpp file2.cpp ...
```

- `-Wall`: compiler will report all warnings
- `-std=c++17`: the code will be compiled using the C++17 standard
- `-g`: the executable file will contain debugging symbols, allowing *valgrind* to create better reports
- `-o ws`: the compiled application will be named `ws`

After compiling and testing your code, run your program as following to check for possible memory leaks (assuming your executable name is `ws`):

```bash
valgrind ws
```

To check the output, use a program that can compare text files.  Search online for such a program for your platform, or use *diff* available on `matrix`.

## Part 1 (0%)
The first portion of this workshop consists of modules:
- `w5` (supplied)
- `Job`
- `CentralUnit`
- `Processor`

Enclose all your source code within the `sdds` namespace and include the necessary guards in each header file.

### `Job` module

This module defines a class that holds information about a single job that requires handling.

***Private Data***

Design and code a class named `Job` that should be able to store the following information (for each attribute, you can chose any type you think is appropriate--you must be able to justify the decisions you have made):

- a title describing the job to be done.
- a positive number indicating the units of work to be done to finish the job.
- a positive number indicating the remaining units of work to be done to finish the job.
- a flag to determine if the job is active or not.

***Public Members***
- a default constructor that sets the job to an empty, inactive state.
- a custom constructor that receives the title of the job. For simplicity, the number of units of work to be done to finish the job is equal to the remainder from dividing the number of characters in the title by `10` and adding `1`.
- `is_active()`: a query that returns whether the job is active or not.
- `is_complete()`: a query that returns whether the job is complete or not (no remaining units of work).
- `name()`: a query that returns a copy of the title of the job.
- `display()`: inserts the job details into the output stream (received as an argument) and returns nothing. The output should be displayed in the following format:
  
  ```
  `JOB NAME` [XX/XX remaining]
  ```
  where the `XX`'s are the remaining and total work represented with two digits padded with zeroes.
- overload the appropriate operator to make this object behave like a function object. The purpose of this member is to perform work on the job to progress towards completion. When called, this function takes the units of work handled (as a positive number) as its only argument and reduces the remaining work by it. If there is no remaining work, the job is marked as inactive. If the handled work is more than the remaining work, the remaining work is set to `0` and your function reports an `std::underflow_error` to the caller.

***FREE Helpers***
- `std::ostream& operator<<(std::ostream&, Job&)`: displays the job details.

**Add any other function that is required by your design, but make sure they are private members!**

### `Central Unit` module

This module defines a family of classes that represents a central (or managing or main) unit that hosts and coordinates individual units to handle jobs.

***Private Data***

Design and code a family of classes named `CentralUnit`. Since you are creating a family of classes, its members must be defined in the header file. A `CentralUnit` object stores the following information:
- **std::string m_type**: a short name describing the type of work this central unit will be coordinating.
- **T\*\* m_items**: a dynamically-allocated array of pointers to individual units of type `T` (i.e. any type). These are the units that will be hosted in the `CentralUnit` object.
- **Job\* m_jobs[ ]**: a statically-allocated array of pointers to jobs that are queued up and waiting to be handled by an individual unit when the central unit is run. Only a maximum of 4 jobs can be queued up at any given time.
- **size_t m_size**: stores the number of individual units hosted by the central unit.
- **size_t m_count**: stores the number of jobs queued up and waiting to be handled.

***Public Data***

- **std::ostream& log**: a class member that stores a reference to an output stream that will be used for logging information. Defaults to `std::cout`.

***Public Members***

- a custom constructor that receives the type of work handled by the central unit as its first argument and a C-style null-terminated string holding the name of a file that will initialize this object as its second argument. Each line in the file provided will hold information about an individual unit that this object hosts, formatted as: 
  ```
  UNIT_TYPE | UNIT_NAME | WORK_CAPACITY
  ```
  If the file cannot be opened, report an `std::invalid_argument` error with the messsage `File cannot be opened.`. Create a store the individual units based on each line and remove all leading and trailing spaces for each token. Consider using [std::stoi()](https://en.cppreference.com/w/cpp/string/basic_string/stol) to parse `WORK_CAPACITY` as a positive number.
  
  *Note: `std::stoi` can report an error if it fails to convert `WORK_CAPACITY` to a number. Capture and handle this error by defaulting to a work capacity of `1`*.
  
  ***ASSUMPTION***: In this design, the constructor for `T` takes the address of the hosting central unit (the current object in this case) as its first argument, two strings as its next two arguments (the unit type and name), and a positive number (work capacity) as its last argument.
- all standard member functions needed to properly handle the dynamically-allocated data member. This design does not support copy operations -- if creating a new instance from a copy, report an exception, and assigning a copy of a `CentralUnit` should result in a compile-time error.
- `operator+=()`: takes the name of a job as an argument, creates a new `Job` object that is added to the job queue, and returns a reference to the current central unit. If the queue is full, report an error of type `std::string`.
- `run()`: runs a cycle for each individual unit. Goes through every unit and runs it once. While going through every unit, if there are jobs queued up and a unit is available (has no job assigned), remove the last job from the queue and assign it to the unit before running the unit.
  
  ***ASSUMPTION***: In this design, units of type `T` implement a `run()` method that does work towards completing a job.
- `has_jobs()`: a query that returns if there are any jobs assigned to its units or waiting to be assigned to a unit. This query does not change the state of the central unit.
- `get_available_units()`: a query that returns the number of units without jobs assigned to them. This query does not change the state of the central unit.

**Add any other function that is required by your design, but make sure they are private members!**

### `Processor` Module

This module defines a microprocessor as a specific type of individual unit that can process a job.

***Private Data***

Design and code a class named `Processor` that stores the following information (for each attribute, you can chose any type you think is appropriate--you must be able to justify the decisions you have made):
- **m_host**: stores the address of the hosting central unit that specifically hosts processors.
- **m_brand**: stores the name of the brand of microprocessor, representing the unit type.
- **m_code**: stores a short text descriptor of the microprocessor, representing the unit name.
- **m_power**: stores the number of work units that the microprocessor can process for a job in a single run, representing the unit's work capacity.
- **m_current**: stores the address of the job currently assigned to the microprocessor to be processed.

***Public Members***

- a custom constructor that takes the address of the hosting central unit, the brand, code, and power of the microprocessor as arguments and uses this data to initialize the processor.
- `void run()` - if a job has been assigned to this processor first check if it has been completed, it if has then it can be cleared and removed from this processor. If it is incomplete then perform `m_power` units of work on the job assigned to this processor. If an `std::underflow_error` occurs, handle it by logging an error using the hosting central unit with the message `Processed over quota for ` followed by the job details, and then clearing and removing the job assigned to this processor. This member does nothing if the processor isn't hosted or no job is assigned to it.
- `explicit operator bool() const` - a true/false representation of the processor that returns `true` if a job is assigned to it, `false` otherwise.
- `Processor& operator+=(Job*&)` - assigns a job to the processor. Report an exception if there is a job already assigned.
- `Job* get_current_job() const` - a query that returns the job currently assigned to the processor.

**Add any other function that is required by your design, but make sure they are private members!**

### `w5` Module (supplied)

The tester module for this portion has been supplied. **Do not modify the existing code!**

When doing the workshop, you are encouraged to write your own tests, focusing on a single implemented feature at the time, until you get all functionality in place.

### Sample Output

When the program is started with the command (the file `processors.txt` is provided):
```bash
ws processors.txt
```
the output should look like the one from the `sample_output.txt` file.

### Test Your Code

To test the execution of your program, use the same data as shown in the output example above.

Upload your source code to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```bash
~profname.proflastname/submit 345_w5_p1
```
and follow the instructions.

***This part represents a milestone in completing the workshop and is not marked!***

## Part 2 (100%)

The second part of this workshop upgrades your solution using the [observer pattern](https://wikipedia.org/wiki/Observer_pattern) to handle when a job is complete or encounters an error  during processing.

- `Processor` (to be updated)
- `CentralUnit` (to be updated)
- `w5` (partially supplied)

### `Processor` Module

Update the `Processor` module to run it like a functor and register callbacks to execute in specific cases.

***Private Data***

- a data member that stores the address of a function that will be run when a job finishes processing. The function returns nothing and takes a hosting central unit by reference as its first argument and the address of a processor as its second argument.
- an [`std::function`](https://en.cppreference.com/w/cpp/utility/functional/function) object that targets a function to be run when an error occurs. The function targetted returns nothing and takes the address of a processor as its only argument.

***Public Members***

- `on_complete()`: takes the address of a callback function to register and run when a job finishes processing as an argument and sets the respective instance member. This function returns nothing.
- `on_error()`: takes, as an argument, an `std::function` callback to register and run when a job encounters an error during processing and sets the respective instance member. This function returns nothing.
- an operator overload to make a `Processor`  a functor. This function runs the processor once, similar to `run()`. If the job assigned to the processor was already completed, do nothing. If the assigned job is completed after performing `m_power` units of work on it, this function calls the appropriate callback registered, if any. If the job reports an `std::underflow_error`, handle it by calling the registered error callback, if any.
- `free()`: makes the processor available by unassigning the current job (do not clear any memory allocated for it) and returning the address of the job that was unassigned.

***Friend Helpers***
- `std::ostream& operator<<(std::ostream&, const Processor&)`: inserts the details about this processor into the output stream in the following format:
  ```
  (POWER) BRAND CODE processing CURRENT_JOB_DETAILS
  ```
  if the processor is not assigned a job, only print out the power, brand, and code.

### `CentralUnit` Module

Update the `CentralUnit` module to handle a job completion and error.

***Public members***

- `complete_job()`: a class member function that receives a central unit (by reference) and the address of a type `T` unit as its arguments. This function frees the unit received and clears memory allocated for the job that was assigned to that unit. This function also logs the following:
  
  ```
  [COMPLETE] JOB_DETAILS using UNIT_DETAILS
  AVAILABLE_UNITS units available.
  ```
  use the insertion operator to log the `JOB_DETAILS` and `UNIT_DETAILS`. 
- custom constructor ***(to be updated)***: update your custom constructor to register callbacks with units. For each unit created: 
  - register the class member function `complete_job()` as a callback for a job completion with the unit.
  - register a lambda function that will make the unit received as as argument available and clears memory allocated for the job that was assigned to that unit. The lambda also uses the error logging object to log the following:
    ```
    Failed to complete job JOB_NAME
    AVAILABLE_UNITS units available
    ```
    where `JOB_NAME` is the name of the job with the error and `AVAILABLE_UNITS` is the number of available units in this central unit.
- `run()` ***(to be updated)***: Update the `run()` function to run the unit by using it as a functor instead of calling the unit's `run()` function.
- `operator+=()`: receives the address of a unit (takes ownership) and adds it to the central unit (resize the data member if needed). Assign the necessary job error and completion callbacks (similar to above) to this newly added unit. If the unit received is not available, this function does not add it and reports an exception instead.
- `operator[]()`: a query that receives the title of a job as a C-style null-terminated string and returns a pointer to the unit that is currently assigned a job that matches the given title. If no unit is assigned a matching job, this function reports an `std::out_of_range` error with the message `Job is not being handled by a unit.` This query does not modify the state of the central unit.
- `display()`: a query that receives and returns nothing and displays the central unit's current state. Logs `Central TYPE Unit list` as a heading (`TYPE` is the type of work being done by the central unit). Then logs each individual unit on a separate line in the following format:
  ```
  [XXXX] UNIT_DETAILS
  ```
  where `XXXX` is the unit's index (starting from `1`) in the central unit and is zero-padded. 
  
  This query does not modify the state of the central unit.

### `w5` Module

Complete the singular `TODO` section in `main()`. **Do not modify any other existing code!**

### Sample Output

When the program is started with the command (the files are provided):
```bash
ws processors.txt
```
the output should look like the one from the `sample_output.txt` file.

### Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this particular workshop and mention any issues that caused you difficulty and how you solved them. Include in your explanation—**but do not limit it to**—the following points:
- Identify which components of your solution are the observers, subjects, and the events per the observer pattern. You can read online about the [Observer Pattern](https://en.wikipedia.org/wiki/Observer_pattern). **Justify your answer!**
- Why did we need to use an `std::function` object? What are the pros and cons of using it (mention at least 1 of each)?
- How can C++ templates be used instead of an `std::function` object to store a function?
- Your code reports and handles different types of exceptions. How would you modify your code to only report exceptions of the same data type and handle them appropriately? How would you differentiate between the different exceptions in this case?

To avoid deductions, refer to code in your solution as examples to support your explanations.

### Submission

To test and demonstrate execution of your program use the same data as shown in the output example above.

Upload the source code and the reflection file to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```bash
~profname.proflastname/submit 345_w5_p2
```
and follow the instructions.

**:warning:Important:** Please note that a successful submission does not guarantee full credit for this workshop. If the professor is not satisfied with your implementation, your professor may ask you to resubmit. Resubmissions will attract a penalty.