# Doctor Appointment Booking System

This project is a Doctor Appointment Booking System that allows patients to register, login, create, view, and cancel appointments with doctors. The system ensures that appointments are unique and handles various edge cases such as invalid inputs and double bookings. The application is built using C++ and leverages the [nlohmann/json](https://github.com/nlohmann/json) library for handling JSON data.

## Features

- **Patient Registration**: Patients can register by providing their name, phone number, email, and password.
- **Patient Login**: Registered patients can log in using their email and password.
- **Create Appointment**: Patients can create appointments with doctors by selecting available dates and time slots.
- **View Appointments**: Patients can view their upcoming appointments.
- **Cancel Appointment**: Patients can cancel their appointments, and the system will update the doctor's availability.
- **Update Patient Details**: Patients can update their personal details.

## Technologies Used

- **C++**: The core programming language used for the application.
- **nlohmann/json**: A JSON library for C++ to handle JSON data.
- **Make**: A build system to manage the build process.

## Project Structure

```
.
├── data
│   ├── doctors.json
│   ├── patients.json
├── include
│   ├── CLI.h
│   ├── DataValidator.h
|   ├── json.hpp
│   ├── JsonHandler.h
│   ├── Patient.h
│   ├── User.h
├── src
│   ├── CLI.cpp
│   ├── DataValidator.cpp
│   ├── JsonHandler.cpp
│   ├── main.cpp
│   ├── Patient.cpp
│   ├── User.cpp
├── .gitignore
├── Makefile
└── README.md


```

## Getting Started

### Prerequisites

- **C++ Compiler**: Ensure you have a C++ compiler installed (e.g., g++, clang++).
- **Make**: Ensure you have Make installed.

### Building the Project

1. Clone the repository:

   ```sh
   git clone https://github.com/masum414/Doctor-Appointment-Booking-System.git
   cd Doctor-Appointment-Booking-System
   ```

2. Build the project:
   ```sh
   make
   ```

### Running the Application

After building the project, you can run the application from the project directory:

```sh
./DoctorAppointmentBookingSystemApp
```

## JSON Data Files

### doctors.json

This file contains the list of doctors and their available appointments.

```json
[
  {
    "ID": 2501,
    "Name": "Dr. Abdullah Al Mamun",
    "Specialization": "Cardiology",
    "Appointments": {
      "2025-01-01": {
        "09:00": true,
        "09:30": true,
        "10:00": true
      }
    }
  }
]
```

### patients.json

This file contains the list of registered patients and their appointments.

```json
[
  {
    "ID": 1,
    "Name": "Masum",
    "Phone": "+8801700000000",
    "Email": "masum@gmail.com",
    "Password": "masum1234@#",
    "Appointments": [
      {
        "doctorID": 2501,
        "date": "2025-01-01",
        "timeSlot": "09:00"
      }
    ]
  }
]
```

## License

This project is licensed under the [MIT License](LICENSE). You can use and modify the code as per the license terms.
