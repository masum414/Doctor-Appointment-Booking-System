CC = g++
CFLAGS = -std=c++11 -Wall -Iinclude
SRC = src/main.cpp src/User.cpp src/Doctor.cpp src/Patient.cpp src/Appointment.cpp src/JsonHandler.cpp src/DataValidator.cpp src/CLI.cpp
OBJ = $(SRC:.cpp=.o)
EXEC = DoctorAppointmentBookingSystemApp

all: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ) $(EXEC)