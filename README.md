-- What is it?
This tool generates a timetable parameterised by the user. I made it for a textbook I was working through so that I would know how long it will take me to get through all its questions. It could probably be generalised relatively easily to tasks, however now it is suited to book questions.

-- How does it work?
It creates a vector of Days, each Day containing a hashmap of chapter number - a vector of question numbers which will be completed that day. To display the timetable, you then iterate over this vector of days and print the question numbers (with their associated chapter). 

To build this vector of Days, you supply the timetable with a fair amount of information including:

a vector of how many questions are in each chapter, the order in which you would like the chapters completed, any questions you have already completed, any so called "problem questions" which cannot be completed in their respective chapter as they depend upon a future chapter etc.

It then creates a hashmap of chapter number -> linked list of that chapter's questions. To accommodate the problem questions, it simply cuts them out of their linked list and pastes them onto the end of the chapter's linked list they depend upon.

-- To use
Include "timetable.h" in your main.cpp, send the required info through to Timetable's constructor, then run build_timetable(), build_schedule() and print_schedule() to see your timetable.

-- Is it as efficient as it can be?
Almost certainly not. It even had a method to write the timetable to a semi colon delimited file at some point, but I took that out.
