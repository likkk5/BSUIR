using System;
using HotelManagementSystem.Data;
using HotelManagementSystem.Models;
using HotelManagementSystem.Services;
using Npgsql;

class Program
{
    private static UserService _userService;
    private static RoomService _roomService;
    private static ReservationService _reservationService;
    private static NotificationService _notificationService;
    private static GuestService _guestService;
    private static ServiceService _serviceService;
    private static ServiceInOrderService _serviceInOrderService;
    private static OrderService _orderService;
    private static FeedbackService _feedbackService;
    private static RoleService _roleService;
    static void Main(string[] args)
    {
        // Указываем параметры подключения
        string host = "localhost";
        string database = "hotel_management_system";
        string username = "postgres";
        string password = "1111";

        // Создаем объект DatabaseManager
        DatabaseManager dbManager = new DatabaseManager(host, database, username, password);

        // Инициализируем сервисы
        _userService = new UserService(dbManager);
        _roomService = new RoomService(dbManager);
        _reservationService = new ReservationService(dbManager);
        _notificationService = new NotificationService(dbManager);
        _guestService = new GuestService(dbManager);
        _serviceService = new ServiceService(dbManager);
        _feedbackService = new FeedbackService(dbManager);
        _serviceInOrderService = new ServiceInOrderService(dbManager);
        _orderService = new OrderService(dbManager);
        _roleService = new RoleService(dbManager);
        // Подключение к базе данных
        try
        {
            using (var connection = dbManager.GetConnection())
            {
                connection.Open();
                Console.WriteLine("Успешно подключено к базе данных!");
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка подключения к базе данных: {ex.Message}");
            return;
        }

        // Основное меню
        MainMenu();
    }

    private static void MainMenu()
    {
        while (true)
        {
            Console.WriteLine("\nДобро пожаловать в систему управления отелем!");
            Console.WriteLine("Выберите действие:");
            Console.WriteLine("1. Авторизация");
            Console.WriteLine("2. Регистрация");
            Console.WriteLine("3. Просмотреть список услуг");
            Console.WriteLine("4. Просмотреть список номеров");
            Console.WriteLine("5. Выход");

            string choice = Console.ReadLine();

            switch (choice)
            {
                case "1":
                    Login();
                    break;
                case "2":
                    RegisterUser();
                    break;
                case "3":
                    ViewServices();
                    break;
                case "4":
                    ViewRooms();
                    break;
                case "5":
                    Console.WriteLine("До свидания!");
                    return;
                default:
                    Console.WriteLine("Неверный выбор. Попробуйте снова.");
                    break;
            }
        }
    }

    private static void ViewServices()
    {
        Console.WriteLine("\nСписок услуг отеля:");
        var services = _serviceService.GetAllServices();
        foreach (var service in services)
        {
            Console.WriteLine($"Услуга: {service.Name}, Цена: {service.Cost:C}");
        }
    }

    private static void ViewRooms()
    {
        Console.WriteLine("\nСписок номеров отеля:");
        var rooms = _roomService.GetAllRooms();
        foreach (var room in rooms)
        {
            Console.WriteLine($"Номер: {room.RoomNumber}, Тип: {room.RoomType}, Цена за ночь: {room.CostForNight:C}");
        }
    }

    private static void Login()
    {
        Console.WriteLine("\nВведите логин:");
        string login = Console.ReadLine();
        Console.WriteLine("Введите пароль:");
        string password = Console.ReadLine();

        var user = _userService.Authenticate(login, password);
        if (user != null)
        {
            Console.WriteLine($"Добро пожаловать, {user.FirstName}! Ваша роль: {user.RoleId}");
            RoleMenu(user);
        }
        else
        {
            Console.WriteLine("Ошибка авторизации. Неверный логин или пароль.");
        }
    }

    private static void RegisterUser()
    {
        Console.WriteLine("\nРегистрация нового пользователя");
        Console.WriteLine("Введите имя:");
        string firstName = Console.ReadLine();
        Console.WriteLine("Введите фамилию:");
        string lastName = Console.ReadLine();
        Console.WriteLine("Введите логин:");
        string login = Console.ReadLine();
        Console.WriteLine("Введите пароль:");
        string password = Console.ReadLine();
        Console.WriteLine("Введите email:");
        string email = Console.ReadLine();
        Console.WriteLine("Введите вашу роль (1 - Admin, 2 - Employee, 3 - Guest):");
        int roleId = int.Parse(Console.ReadLine());

        var user = new User
        {
            FirstName = firstName,
            LastName = lastName,
            Login = login,
            Password = password,
            RoleId = roleId,
            Email = email
        };

        try
        {
            // Один вызов AddUser
            user.Id = _userService.AddUser(user);

            if (roleId == 3) // Если роль - Гость
            {
                // Запрашиваем паспорт и место проживания
                Console.WriteLine("Введите номер паспорта:");
                string passportNumber = Console.ReadLine();
                Console.WriteLine("Введите место проживания:");
                string residence = Console.ReadLine();

                // Добавляем информацию в таблицу guest
                var guest = new Guest
                {
                    UserId = user.Id,
                    PassportNumber = passportNumber,
                    Residence = residence
                };

                _guestService.AddGuest(guest);
                Console.WriteLine("Гостевая информация успешно добавлена!");
            }

            Console.WriteLine("Регистрация успешна!");
        }
        catch (Npgsql.PostgresException ex) when (ex.SqlState == "23505")
        {
            Console.WriteLine("Ошибка: введённый логин или email уже используется. Пожалуйста, выберите другие данные.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Произошла ошибка: {ex.Message}");
        }
    }

    private static void RoleMenu(User user)
    {
        switch (user.RoleId)
        {
            case 1: // Admin
                AdminMenu(user);
                break;
            case 2: // Employee
                EmployeeMenu(user);
                break;
            case 3: // Guest
                GuestMenu(user);
                break;
            default:
                Console.WriteLine("Неизвестная роль. Доступ запрещен.");
                break;
        }
    }

    private static void AdminMenu(User user)
    {
        while (true)
        {
            Console.WriteLine("\nАдминистраторское меню:");
            Console.WriteLine("1. Управление пользователями");
            Console.WriteLine("2. Просмотр всех бронирований");
            Console.WriteLine("3. Управление ролями пользователей");
            Console.WriteLine("4. Управление номерами");
            Console.WriteLine("5. Управление сервисами");
            Console.WriteLine("6. Выход");

            string choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    ManageUsers();
                    break;
                case "2":
                    ViewAllReservations();
                    break;
                case "3":
                    ManageRoles();
                    break;
                case "4":
                    ManageRooms();
                    break;
                case "5":
                    ManageServices();
                    break;
                case "6":
                    return;
                default:
                    Console.WriteLine("Неверный выбор. Попробуйте снова.");
                    break;
            }
        }
    }


    private static void EmployeeMenu(User user)
    {
        while (true)
        {
            Console.WriteLine("\nМеню сотрудника:");
            Console.WriteLine("1. Просмотр списка номеров для уборки");
            Console.WriteLine("2. Изменить статус номера");
            Console.WriteLine("3. Просмотр заказанных услуг");
            Console.WriteLine("4. Изменить статус услуги");
            Console.WriteLine("5. Отправить уведомление");
            Console.WriteLine("6. Переключиться в меню гостя");
            Console.WriteLine("7. Выход");

            string choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    ViewCleaningList();
                    break;
                case "2":
                    EditRoomStatus();
                    break;
                case "3":
                    ViewOrderedServices();
                    break;
                case "4":
                    EditServiceStatus();
                    break;
                case "5":
                    SendNotification();
                    break;
                case "6":
                    GuestMenu(user);
                    break;
                case "7":
                    return;
                default:
                    Console.WriteLine("Неверный выбор. Попробуйте снова.");
                    break;
            }
        }
    }


    private static void GuestMenu(User user)
    {
        while (true)
        {
            Console.WriteLine("\nМеню гостя:");
            Console.WriteLine("1. Просмотр доступных номеров");
            Console.WriteLine("2. Забронировать номер");
            Console.WriteLine("3. Просмотр истории бронирований");
            Console.WriteLine("4. Отменить бронирование");
            Console.WriteLine("5. Список услуг");
            Console.WriteLine("6. Просмотр истории заказанных услуг");
            Console.WriteLine("7. Заказать услугу");
            Console.WriteLine("8. Редактировать заказ");
            Console.WriteLine("9. Оставить отзыв");
            Console.WriteLine("10. Редактировать отзыв");
            Console.WriteLine("11. Удалить отзыв");
            Console.WriteLine("12. Просмотр уведомлений"); // Новый пункт для уведомлений
            Console.WriteLine("13. Выход");

            string choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    ViewAvailableRoomsProcedure();
                    break;
                case "2":
                    ReserveRoom(user);
                    break;
                case "3":
                    ViewReservationHistory(user);
                    break;
                case "4":
                    CancelReservation(user);
                    break;
                case "5":
                    ViewServices();
                    break;
                case "6":
                    ViewServiceHistory(user);
                    break;
                case "7":
                    OrderService(user);
                    break;
                case "8":
                    EditOrder(user);
                    break;
                case "9":
                    LeaveFeedback(user);
                    break;
                case "10":
                    EditFeedback(user);
                    break;
                case "11":
                    DeleteFeedback(user);
                    break;
                case "12":
                    ViewNotifications(user);
                    break;
                case "13":
                    return;
                default:
                    Console.WriteLine("Неверный выбор. Попробуйте снова.");
                    break;
            }
        }
    }



    private static void ManageUsers()
    {
        Console.WriteLine("Управление пользователями (CRUD).");
        Console.WriteLine("1. Создать пользователя");
        Console.WriteLine("2. Просмотреть всех пользователей");
        Console.WriteLine("3. Обновить пользователя");
        Console.WriteLine("4. Удалить пользователя");
        Console.WriteLine("Выберите действие: ");
        string choice = Console.ReadLine();

        switch (choice)
        {
            case "1":
                Console.WriteLine("Введите имя:");
                string firstName = Console.ReadLine();
                Console.WriteLine("Введите фамилию:");
                string lastName = Console.ReadLine();
                Console.WriteLine("Введите логин:");
                string login = Console.ReadLine();
                Console.WriteLine("Введите пароль:");
                string password = Console.ReadLine();
                Console.WriteLine("Введите вашу роль (1 - Admin, 2 - Employee, 3 - Guest):");
                int roleId = int.Parse(Console.ReadLine());
                Console.WriteLine("Введите почту:");
                string email = Console.ReadLine();

                var newUser = new User
                {
                    FirstName = firstName,
                    LastName = lastName,
                    Login = login,
                    Password = password,
                    RoleId = roleId,
                    Email = email
                };

                _userService.AddUser(newUser);
                Console.WriteLine("Пользователь успешно добавлен.");
                break;

            case "2":
                var users = _userService.GetAllUsers();
                foreach (var user in users)
                {
                    Console.WriteLine($"ID: {user.Id}, Имя: {user.FirstName} {user.LastName}, Логин: {user.Login}, Пароль: {user.Password}, Роль: {user.RoleId}, Почта: {user.Email}");
                }
                break;

            case "3":
                Console.WriteLine("Введите ID пользователя для обновления:");
                int userIdToUpdate = int.Parse(Console.ReadLine());
                var userToUpdate = _userService.GetUserById(userIdToUpdate);
                if (userToUpdate == null)
                {
                    Console.WriteLine("Пользователь не найден.");
                    return;
                }

                Console.WriteLine($"Введите новое имя (текущее: {userToUpdate.FirstName}):");
                string newFirstName = Console.ReadLine();
                if (!string.IsNullOrEmpty(newFirstName)) userToUpdate.FirstName = newFirstName;

                Console.WriteLine($"Введите новую фамилию (текущая: {userToUpdate.LastName}):");
                string newLastName = Console.ReadLine();
                if (!string.IsNullOrEmpty(newLastName)) userToUpdate.LastName = newLastName;

                Console.WriteLine($"Введите новый логин (текущий: {userToUpdate.Login}):");
                string newLogin = Console.ReadLine();
                if (!string.IsNullOrEmpty(newLogin)) userToUpdate.Login = newLogin;

                Console.WriteLine($"Введите новый пароль (текущий: {userToUpdate.Password}):");
                string newPassword = Console.ReadLine();
                if (!string.IsNullOrEmpty(newPassword)) userToUpdate.Password = newPassword;

                Console.WriteLine($"Введите новую почту (текущая: {userToUpdate.Email}):");
                string newEmail = Console.ReadLine();
                if (!string.IsNullOrEmpty(newEmail)) userToUpdate.Email = newEmail;

                _userService.UpdateUser(userToUpdate);
                Console.WriteLine("Пользователь успешно обновлен.");
                break;

            case "4":
                Console.WriteLine("Введите ID пользователя для удаления:");
                int userIdToDelete = int.Parse(Console.ReadLine());
                _userService.DeleteUser(userIdToDelete);
                Console.WriteLine("Пользователь успешно удален.");
                break;

            default:
                Console.WriteLine("Неверный выбор.");
                break;
        }
    }

    private static void ViewAllReservations()
    {
        Console.WriteLine("Просмотр всех бронирований.");
        var reservations = _reservationService.GetAllReservations();
        foreach (var reservation in reservations)
        {
            Console.WriteLine($"ID: {reservation.Id}, Гость: {reservation.GuestId}, Номер: {reservation.RoomNumber}");
        }
    }

    private static void ViewAvailableRooms()
    {
        Console.WriteLine("Просмотр доступных номеров.");
        var availableRooms = _roomService.GetAvailableRooms();
        if (availableRooms.Count == 0)
        {
            Console.WriteLine("Нет доступных номеров.");
        }
        else
        {
            foreach (var room in availableRooms)
            {
                Console.WriteLine($"Номер: {room.RoomNumber}, Тип: {room.RoomType}, Цена: {room.CostForNight}");
            }
        }
    }
    private static void ViewAvailableRoomsProcedure()
    {
        Console.WriteLine("Просмотр доступных номеров.");
        Console.WriteLine("Введите дату заселения (yyyy-MM-dd):");
        DateTime checkInDate = DateTime.Parse(Console.ReadLine());
        Console.WriteLine("Введите дату выезда (yyyy-MM-dd):");
        DateTime checkOutDate = DateTime.Parse(Console.ReadLine());

        try
        {
            var availableRooms = _roomService.GetAvailableRoomsProcedure(checkInDate, checkOutDate);

            if (availableRooms.Count == 0)
            {
                Console.WriteLine("Нет доступных номеров.");
            }
            else
            {
                foreach (var room in availableRooms)
                {
                    Console.WriteLine($"Номер: {room.RoomNumber}, Тип: {room.RoomType}");
                }
            }
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при просмотре доступных номеров: {ex.Message}");
            Console.WriteLine($"Трассировка стека: {ex.StackTrace}");
        }
    }

    private static void ReserveRoom(User user)
    {
        try
        {
            Console.WriteLine("Бронирование номера.");
            Console.WriteLine("Введите номер комнаты:");
            string roomNumber = Console.ReadLine();
            Console.WriteLine("Введите дату заселения (yyyy-MM-dd):");
            DateTime checkInDate = DateTime.Parse(Console.ReadLine());
            Console.WriteLine("Введите дату выезда (yyyy-MM-dd):");
            DateTime checkOutDate = DateTime.Parse(Console.ReadLine());

            // Получение GuestId по UserId
            int guestId = _guestService.GetGuestIdByUserId(user.Id);
            if (guestId == 0)
            {
                Console.WriteLine("Ошибка: пользователь не зарегистрирован как гость.");
                return;
            }
            // Вычисление общей стоимости через метод CalculateBookingCost
            decimal totalCost = _roomService.CalculateBookingCost(roomNumber, checkInDate, checkOutDate);
            if (totalCost == 0)
            {
                Console.WriteLine("Ошибка: не удалось рассчитать стоимость бронирования.");
                return;
            }

            var reservation = new Reservation
            {
                GuestId = guestId,
                RoomNumber = roomNumber,
                CheckInDate = checkInDate,
                CheckOutDate = checkOutDate,
                ReservationDate = DateTime.Now,
                ReservationStatus = "Pending",
                Cost = totalCost
            };

            _reservationService.AddReservation(reservation);
            Console.WriteLine("Бронирование успешно добавлено!");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при выполнении бронирования: {ex.Message}");
        }
    }

    private static void ViewReservationHistory(User user)
    {
        Console.WriteLine("Просмотр истории бронирований.");
        var reservations = _reservationService.GetReservationsByUser(user.Id);
        if (reservations.Count == 0)
        {
            Console.WriteLine("Нет бронирований для данного пользователя.");
        }
        else
        {
            foreach (var reservation in reservations)
            {
                Console.WriteLine($"ID: {reservation.Id}, Комната: {reservation.RoomNumber}, Заселение: {reservation.CheckInDate:yyyy-MM-dd}, Выезд: {reservation.CheckOutDate:yyyy-MM-dd}, Статус: {reservation.ReservationStatus}, Цена: {reservation.Cost:C}");
            }
        }
    }
    private static void ViewServiceHistory(User user)
    {
        var servicesInOrders = _serviceInOrderService.GetServicesByOrderId(user.Id); // Получаем услуги пользователя
        if (servicesInOrders.Count == 0)
        {
            Console.WriteLine("Нет заказанных услуг.");
            return;
        }

        Console.WriteLine("\nИстория заказанных услуг:");
        foreach (var serviceInOrder in servicesInOrders)
        {
            var service = _serviceService.GetServiceById(serviceInOrder.ServiceId);
            var order = _orderService.GetOrderById(serviceInOrder.OrderId);

            Console.WriteLine($"Услуга: {service.Name}");
            Console.WriteLine($"Стоимость: {service.Cost} руб.");
            Console.WriteLine($"Количество: {serviceInOrder.Amount}");
            Console.WriteLine($"Дата заказа: {order.OrderDateTime}");
            Console.WriteLine($"Статус заказа: {order.OrderStatus}");
            Console.WriteLine();
        }
    }

    private static bool ReservationExists(int reservationId, int userId)
    {
        // Шаг 1: Получить резервацию по ID
        var reservation = _reservationService.GetReservationById(reservationId);
        if (reservation == null)
        {
            Console.WriteLine("Бронирование не найдено.");
            return false;
        }

        Console.WriteLine($"Бронирование найдено. GuestId: {reservation.GuestId}");

        // Шаг 2: Получить гостя по GuestId из резервации
        var guest = _guestService.GetGuestById(reservation.GuestId);
        if (guest == null)
        {
            Console.WriteLine("Гость не найден.");
            return false;
        }

        Console.WriteLine($"Гость найден. UserId: {guest.UserId}");

        // Шаг 3: Сравнить UserId из гостя с UserId пользователя
        bool isOwner = guest.UserId == userId;
        Console.WriteLine($"Пользователь является владельцем бронирования: {isOwner}");

        return isOwner;
    }

    private static void OrderService(User user)
    {
        Console.WriteLine("Заказ услуги:");

        // Получение ID брони
        Console.WriteLine("Введите ID брони:");
        int reservationId = int.Parse(Console.ReadLine());

        // Проверяем существование брони
        if (!ReservationExists(reservationId, user.Id))
        {
            Console.WriteLine("Ошибка: такая бронь не существует или не привязана к вашему аккаунту.");
            return;
        }

        // Получение доступных услуг
        var availableServices = _serviceService.GetAllServices();
        if (availableServices.Count == 0)
        {
            Console.WriteLine("Нет доступных услуг.");
            return;
        }

        Console.WriteLine("Доступные услуги:");
        for (int i = 0; i < availableServices.Count; i++)
        {
            Console.WriteLine($"{i + 1}. {availableServices[i].Name} - {availableServices[i].Cost} руб.");
        }

        // Выбор услуги
        Console.WriteLine("Выберите услугу (номер):");
        int serviceIndex = int.Parse(Console.ReadLine()) - 1;
        if (serviceIndex < 0 || serviceIndex >= availableServices.Count)
        {
            Console.WriteLine("Некорректный выбор.");
            return;
        }

        // Ввод количества
        Console.WriteLine("Введите количество:");
        int quantity = int.Parse(Console.ReadLine());

        // Создание заказа
        var selectedService = availableServices[serviceIndex];
        var order = new Order
        {
            OrderDateTime = DateTime.Now,
            ReservationId = reservationId,
            OrderStatus = "Pending",
            EmployeeId = user.Id,
            Cost = selectedService.Cost * quantity
        };
        int orderId = _orderService.CreateOrder(order);
        Console.WriteLine($"Создан заказ с ID: {orderId}");

        var serviceInOrder = new ServiceInOrder
        {
            ServiceId = selectedService.Id,
            OrderId = orderId,
            EmployeeId = user.Id,
            Amount = quantity
        };
        _serviceInOrderService.AddServiceToOrder(serviceInOrder);

        // Выводим стоимость заказа
        Console.WriteLine($"Стоимость заказа: {order.Cost} руб.");
        Console.WriteLine("Услуга успешно заказана!");

        // Создание уведомления для пользователя
        var notificationText = $"Вы заказали услугу: {selectedService.Name}. Стоимость: {order.Cost} руб. Статус заказа: {order.OrderStatus}.";
        var notification = new Notification
        {
            NotificationDateTime = DateTime.Now,
            NotificationText = notificationText,
            OrderId = orderId // Связываем уведомление с заказом
        };

        // Сохраняем уведомление
        _notificationService.CreateNotification(notification);

        Console.WriteLine("Уведомление о заказе успешно отправлено.");
    }

    private static void LeaveFeedback(User user)
    {
        Console.WriteLine("Введите текст отзыва:");
        string feedbackText = Console.ReadLine();
        Console.WriteLine("Введите оценку (1-5):");

        if (int.TryParse(Console.ReadLine(), out int rating) && rating >= 1 && rating <= 5)
        {
            // Получаем guest_id для текущего пользователя
            int guestId = _guestService.GetGuestIdByUserId(user.Id);

            if (guestId == 0)
            {
                Console.WriteLine("Ошибка: Гость с таким ID не существует.");
                return; // Прерываем выполнение, если гость не найден
            }

            // Создаем отзыв
            var feedback = new Feedback
            {
                GuestId = guestId, // Используем полученный guest_id
                FeedbackDateTime = DateTime.Now,
                FeedbackText = feedbackText,
                Rating = rating
            };

            _feedbackService.AddFeedback(feedback);
            Console.WriteLine("Ваш отзыв был добавлен.");
        }
        else
        {
            Console.WriteLine("Некорректная оценка.");
        }
    }


    private static void EditFeedback(User user)
    {
        Console.WriteLine("Введите ID отзыва, который хотите отредактировать:");
        if (int.TryParse(Console.ReadLine(), out int feedbackId))
        {
            var feedback = _feedbackService.GetFeedbackById(feedbackId);
            if (feedback != null)
            {
                // Получаем guest_id для текущего пользователя
                int guestId = _guestService.GetGuestIdByUserId(user.Id);

                // Проверяем, что отзыв принадлежит текущему пользователю
                if (feedback.GuestId == guestId)
                {
                    Console.WriteLine("Введите новый текст отзыва:");
                    feedback.FeedbackText = Console.ReadLine();
                    Console.WriteLine("Введите новую оценку (1-5):");
                    if (int.TryParse(Console.ReadLine(), out int rating) && rating >= 1 && rating <= 5)
                    {
                        feedback.Rating = rating;
                        _feedbackService.UpdateFeedback(feedback);
                        Console.WriteLine("Ваш отзыв был обновлен.");
                    }
                    else
                    {
                        Console.WriteLine("Некорректная оценка.");
                    }
                }
                else
                {
                    Console.WriteLine("Вы не можете редактировать этот отзыв, так как он принадлежит другому пользователю.");
                }
            }
            else
            {
                Console.WriteLine("Отзыв не найден.");
            }
        }
        else
        {
            Console.WriteLine("Некорректный ввод.");
        }
    }

    private static void DeleteFeedback(User user)
    {
        Console.WriteLine("Введите ID отзыва, который хотите удалить:");
        if (int.TryParse(Console.ReadLine(), out int feedbackId))
        {
            var feedback = _feedbackService.GetFeedbackById(feedbackId);
            if (feedback != null)
            {
                // Получаем guest_id для текущего пользователя
                int guestId = _guestService.GetGuestIdByUserId(user.Id);

                // Проверяем, что отзыв принадлежит текущему пользователю
                if (feedback.GuestId == guestId)
                {
                    _feedbackService.DeleteFeedback(feedbackId);
                    Console.WriteLine("Ваш отзыв был удален.");
                }
                else
                {
                    Console.WriteLine("Вы не можете удалить этот отзыв, так как он принадлежит другому пользователю.");
                }
            }
            else
            {
                Console.WriteLine("Отзыв не найден.");
            }
        }
        else
        {
            Console.WriteLine("Некорректный ввод.");
        }
    }

    private static void ViewCleaningList()
    {
        Console.WriteLine("Просмотр списка номеров для уборки.");
        var cleaningList = _roomService.GetRoomsForCleaning();
        if (cleaningList.Count == 0)
        {
            Console.WriteLine("Нет номеров для уборки.");
        }
        else
        {
            foreach (var room in cleaningList)
            {
                Console.WriteLine($"Номер комнаты: {room.RoomNumber}");
            }
        }
    }

    private static void ViewNotifications(User user)
    {
        Console.WriteLine("Уведомления о заказанных услугах:");

        // Получаем уведомления для конкретного пользователя
        var notifications = _notificationService.GetOrderNotifications(user.Id); // Передаем user.Id для фильтрации

        // Проверяем, если уведомлений нет
        if (notifications.Count == 0)
        {
            Console.WriteLine("Нет новых уведомлений.");
        }
        else
        {
            // Для каждого уведомления
            foreach (var notification in notifications)
            {
                // Выводим базовую информацию о уведомлении
                Console.WriteLine($"ID Уведомления: {notification.Id}");
                Console.WriteLine($"Дата: {notification.NotificationDateTime:yyyy-MM-dd HH:mm:ss}");
                Console.WriteLine($"Сообщение: {notification.NotificationText}");

                // Выводим информацию о заказе
                if (notification.Order != null)
                {
                    Console.WriteLine($"Заказ ID: {notification.Order.Id}");
                    Console.WriteLine($"Статус заказа: {notification.Order.OrderStatus}");
                    Console.WriteLine($"Стоимость: {notification.Order.Cost} руб.");

                    // Печать информации о связанном бронировании (если есть)
                    if (notification.Order.ReservationId > 0)
                    {
                        var reservation = _reservationService.GetReservationById(notification.Order.ReservationId);
                        if (reservation != null)
                        {
                            Console.WriteLine($"Комната: {reservation.RoomNumber}");
                            Console.WriteLine($"Дата заезда: {reservation.CheckInDate:yyyy-MM-dd}");
                            Console.WriteLine($"Дата выезда: {reservation.CheckOutDate:yyyy-MM-dd}");
                        }
                    }
                }
                else
                {
                    Console.WriteLine("Нет информации о заказе.");
                }

                // Разделитель для читаемости
                Console.WriteLine(new string('-', 40));
            }
        }
    }

    private static void ViewOrderedServices()
    {
        var orderedServices = _orderService.GetAllOrders();
        if (orderedServices.Count == 0)
        {
            Console.WriteLine("Нет заказанных услуг.");
            return;
        }

        Console.WriteLine("Список заказанных услуг:");
        foreach (var order in orderedServices)
        {
            Console.WriteLine($"ID заказа: {order.Id}, Дата заказа: {order.OrderDateTime}, Стоимость: {order.Cost}, Статус: {order.OrderStatus}");
        }
    }
    private static void EditServiceStatus()
    {
        Console.WriteLine("Введите ID заказа для изменения статуса:");
        int orderId = int.Parse(Console.ReadLine());

        var order = _orderService.GetOrderById(orderId);
        if (order == null)
        {
            Console.WriteLine("Ошибка: заказ с таким ID не найден.");
            return;
        }

        Console.WriteLine($"Текущий статус: {order.OrderStatus}");
        Console.WriteLine("Введите новый статус (например, Confirmed, Processing, Completed):");
        string newStatus = Console.ReadLine();

        order.OrderStatus = newStatus;
        _orderService.UpdateOrder(order);
        Console.WriteLine("Статус заказа успешно обновлен.");
    }
    private static void EditRoomStatus()
    {
        Console.WriteLine("Введите номер комнаты:");
        string roomNumber = Console.ReadLine();

        var room = _roomService.GetRoomByNumber(roomNumber);
        if (room == null)
        {
            Console.WriteLine("Ошибка: номер комнаты не найден.");
            return;
        }

        Console.WriteLine($"Текущий статус: {room.RoomStatus}");
        Console.WriteLine("Введите новый статус (например, Available, Occupied, Cleaning):");
        string newStatus = Console.ReadLine();

        room.RoomStatus = newStatus;
        _roomService.UpdateRoom(room);
        Console.WriteLine("Статус номера успешно обновлен.");
    }
    private static void SendNotification()
    {
        Console.WriteLine("Введите текст уведомления:");
        string message = Console.ReadLine();

        // Запрос на ввод OrderId (ID заказа)
        Console.WriteLine("Введите ID заказа, к которому нужно привязать уведомление:");
        int orderId = int.Parse(Console.ReadLine());

        var notification = new Notification
        {
            NotificationDateTime = DateTime.Now,
            NotificationText = message,
            OrderId = orderId 
        };

        _notificationService.CreateNotification(notification);

        Console.WriteLine("Уведомление успешно отправлено.");
    }

    private static void ManageServices()
    {
        while (true)
        {
            Console.WriteLine("\nМеню управления сервисами:");
            Console.WriteLine("1. Добавить услугу");
            Console.WriteLine("2. Редактировать услугу");
            Console.WriteLine("3. Удалить услугу");
            Console.WriteLine("4. Просмотреть все услуги");
            Console.WriteLine("5. Назад");

            string choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    AddService();
                    break;
                case "2":
                    EditService();
                    break;
                case "3":
                    DeleteService();
                    break;
                case "4":
                    ViewAllServices();
                    break;
                case "5":
                    return;
                default:
                    Console.WriteLine("Неверный выбор. Попробуйте снова.");
                    break;
            }
        }
    }
    private static void AddService()
    {
        Console.WriteLine("Введите название услуги:");
        string serviceName = Console.ReadLine();
        Console.WriteLine("Введите стоимость услуги:");
        decimal serviceCost = decimal.Parse(Console.ReadLine());

        var service = new Service
        {
            Name = serviceName,
            Cost = serviceCost,
        };


        _serviceService.AddService(service);
        Console.WriteLine("Услуга добавлена.");
    }
    private static void EditService()
    {
        Console.WriteLine("Введите ID услуги для редактирования:");
        if (int.TryParse(Console.ReadLine(), out int serviceId))
        {
            var service = _serviceService.GetServiceById(serviceId);
            if (service == null)
            {
                Console.WriteLine("Услуга не найдена.");
                return;
            }

            Console.WriteLine("Введите новое название услуги (или оставьте пустым для сохранения старого):");
            string newServiceName = Console.ReadLine();
            if (!string.IsNullOrEmpty(newServiceName)) service.Name = newServiceName;

            Console.WriteLine("Введите новую стоимость услуги (или оставьте пустым для сохранения старого):");
            if (decimal.TryParse(Console.ReadLine(), out decimal newServiceCost)) service.Cost = newServiceCost;

            _serviceService.UpdateService(service);
            Console.WriteLine("Услуга обновлена.");
        }
        else
        {
            Console.WriteLine("Некорректный ввод ID.");
        }
    }
    private static void DeleteService()
    {
        Console.WriteLine("Введите ID услуги для удаления:");
        if (int.TryParse(Console.ReadLine(), out int serviceId))
        {
            _serviceService.DeleteService(serviceId);
            Console.WriteLine("Услуга удалена.");
        }
        else
        {
            Console.WriteLine("Некорректный ввод ID.");
        }
    }
    private static void ViewAllServices()
    {
        var services = _serviceService.GetAllServices();
        if (services.Count == 0)
        {
            Console.WriteLine("Нет доступных услуг.");
        }
        else
        {
            Console.WriteLine("Доступные услуги:");
            foreach (var service in services)
            {
                Console.WriteLine($"ID: {service.Id}, Название: {service.Name}, Стоимость: {service.Cost} руб.");
            }
        }
    }
    private static void ManageRooms()
    {
        while (true)
        {
            Console.WriteLine("\nМеню управления комнатами:");
            Console.WriteLine("1. Добавить комнату");
            Console.WriteLine("2. Редактировать комнату");
            Console.WriteLine("3. Удалить комнату");
            Console.WriteLine("4. Просмотреть все комнаты");
            Console.WriteLine("5. Просмотреть все доступные комнаты");
            Console.WriteLine("6. Просмотреть комнаты на уборке");
            Console.WriteLine("7. Назад");

            string choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    AddRoom();
                    break;
                case "2":
                    EditRoom();
                    break;
                case "3":
                    DeleteRoom();
                    break;
                case "4":
                    ViewAllRooms();
                    break;
                case "5":
                    ViewAvailableRooms();
                    break;
                case "6":
                    ViewCleaningList();
                    break;
                case "7":
                    return;
                default:
                    Console.WriteLine("Неверный выбор. Попробуйте снова.");
                    break;
            }
        }
    }
    private static void AddRoom()
    {
        Console.WriteLine("Введите номер комнаты:");
        string roomNumber = Console.ReadLine();

        Console.WriteLine("Введите тип комнаты:");
        string roomType = Console.ReadLine();

        Console.WriteLine("Введите стоимость за ночь:");
        decimal costForNight = decimal.Parse(Console.ReadLine());

        Console.WriteLine("Введите статус комнаты (например, 'Available' или 'Cleaning'):");
        string roomStatus = Console.ReadLine();
        var room = new Room
        {
            RoomNumber = roomNumber,
            RoomType = roomType,
            CostForNight = costForNight,
            RoomStatus = roomStatus
        };

        _roomService.AddRoom(room);
        Console.WriteLine("Комната добавлена.");
    }
    private static void EditRoom()
    {
        Console.WriteLine("Введите ID комнаты для редактирования:");
        if (int.TryParse(Console.ReadLine(), out int roomId))
        {
            var room = _roomService.GetRoomById(roomId);
            if (room == null)
            {
                Console.WriteLine("Комната не найдена.");
                return;
            }

            Console.WriteLine("Введите новый номер комнаты (или оставьте пустым для сохранения старого):");
            string newRoomNumber = Console.ReadLine();
            if (!string.IsNullOrEmpty(newRoomNumber)) room.RoomNumber = newRoomNumber;

            Console.WriteLine("Введите новый тип комнаты (или оставьте пустым для сохранения старого):");
            string newRoomType = Console.ReadLine();
            if (!string.IsNullOrEmpty(newRoomType)) room.RoomType = newRoomType;

            Console.WriteLine("Введите новую стоимость за ночь (или оставьте пустым для сохранения старого):");
            if (decimal.TryParse(Console.ReadLine(), out decimal newCostForNight)) room.CostForNight = newCostForNight;

            Console.WriteLine("Введите новый статус комнаты (или оставьте пустым для сохранения старого):");
            string newRoomStatus = Console.ReadLine();
            if (!string.IsNullOrEmpty(newRoomStatus)) room.RoomStatus = newRoomStatus;

            _roomService.UpdateRoom(room);
            Console.WriteLine("Комната обновлена.");
        }
        else
        {
            Console.WriteLine("Некорректный ввод ID.");
        }
    }
    private static void DeleteRoom()
    {
        Console.WriteLine("Введите ID комнаты для удаления:");
        if (int.TryParse(Console.ReadLine(), out int roomId))
        {
            _roomService.DeleteRoom(roomId);
            Console.WriteLine("Комната удалена.");
        }
        else
        {
            Console.WriteLine("Некорректный ввод ID.");
        }
    }
    private static void ViewAllRooms()
    {
        var rooms = _roomService.GetAllRooms();
        if (rooms.Count == 0)
        {
            Console.WriteLine("Нет доступных комнат.");
        }
        else
        {
            Console.WriteLine("Доступные комнаты:");
            foreach (var room in rooms)
            {
                Console.WriteLine($"ID: {room.Id}, Номер: {room.RoomNumber}, Тип: {room.RoomType}, Стоимость: {room.CostForNight} руб., Статус: {room.RoomStatus}");
            }
        }
    }
    private static void AssignRoleToUser()
    {
        Console.WriteLine("Введите ID пользователя:");
        if (int.TryParse(Console.ReadLine(), out int userId))
        {
            // Выводим все доступные роли
            var roles = _roleService.GetAllRoles();
            Console.WriteLine("Доступные роли:");
            foreach (var role in roles)
            {
                Console.WriteLine($"ID: {role.Id}, Название: {role.RoleName}");
            }

            Console.WriteLine("Введите ID роли для назначения:");
            if (int.TryParse(Console.ReadLine(), out int roleId))
            {
                // Присваиваем роль
                _userService.AssignRoleToUser(userId, roleId);
            }
            else
            {
                Console.WriteLine("Неверный ID роли.");
            }
        }
        else
        {
            Console.WriteLine("Неверный ID пользователя.");
        }
    }
    private static void ManageRoles()
    {
        while (true)
        {
            Console.WriteLine("\nМеню управления ролями:");
            Console.WriteLine("1. Добавить роль");
            Console.WriteLine("2. Редактировать роль");
            Console.WriteLine("3. Удалить роль");
            Console.WriteLine("4. Просмотреть все роли");
            Console.WriteLine("5. Присвоить роль пользователю");
            Console.WriteLine("6. Назад");

            string choice = Console.ReadLine();
            switch (choice)
            {
                case "1":
                    AddRole();
                    break;
                case "2":
                    EditRole();
                    break;
                case "3":
                    DeleteRole();
                    break;
                case "4":
                    ViewAllRoles();
                    break;
                case "5":
                    AssignRoleToUser();
                    break;
                case "6":
                    return;
                default:
                    Console.WriteLine("Неверный выбор. Попробуйте снова.");
                    break;
            }
        }
    }
    private static void AddRole()
    {
        Console.WriteLine("Введите название новой роли:");
        string roleName = Console.ReadLine();

        var role = new Role
        {
            RoleName = roleName
        };

        _roleService.AddRole(role);
        Console.WriteLine("Роль добавлена.");
    }
    private static void EditRole()
    {
        Console.WriteLine("Введите ID роли для редактирования:");
        if (int.TryParse(Console.ReadLine(), out int roleId))
        {
            var role = _roleService.GetRoleById(roleId);
            if (role == null)
            {
                Console.WriteLine("Роль не найдена.");
                return;
            }

            Console.WriteLine("Введите новое название роли (или оставьте пустым для сохранения старого):");
            string newRoleName = Console.ReadLine();
            if (!string.IsNullOrEmpty(newRoleName))
            {
                role.RoleName = newRoleName;
            }

            _roleService.UpdateRole(role);
            Console.WriteLine("Роль обновлена.");
        }
        else
        {
            Console.WriteLine("Некорректный ввод ID.");
        }
    }
    private static void DeleteRole()
    {
        Console.WriteLine("Введите ID роли для удаления:");
        if (int.TryParse(Console.ReadLine(), out int roleId))
        {
            _roleService.DeleteRole(roleId);
            Console.WriteLine("Роль удалена.");
        }
        else
        {
            Console.WriteLine("Некорректный ввод ID.");
        }
    }
    private static void ViewAllRoles()
    {
        var roles = _roleService.GetAllRoles();
        if (roles.Count == 0)
        {
            Console.WriteLine("Нет доступных ролей.");
        }
        else
        {
            Console.WriteLine("Доступные роли:");
            foreach (var role in roles)
            {
                Console.WriteLine($"ID: {role.Id}, Название: {role.RoleName}");
            }
        }
    }
    private static void CancelReservation(User user)
    {
        Console.WriteLine("Отмена бронирования.");

        // Получение GuestId по UserId
        int guestId = _guestService.GetGuestIdByUserId(user.Id);
        if (guestId == 0)
        {
            Console.WriteLine("Ошибка: пользователь не зарегистрирован как гость.");
            return;
        }

        Console.WriteLine("Введите ID бронирования, которое хотите отменить:");

        if (!int.TryParse(Console.ReadLine(), out int reservationId))
        {
            Console.WriteLine("Ошибка: ID бронирования должен быть числом.");
            return;
        }

        try
        {
            // Передаём ID бронирования и ID гостя
            _reservationService.CancelReservationProcedure(reservationId, guestId);
            Console.WriteLine($"Бронирование с ID {reservationId} успешно отменено.");
        }
        catch (Exception ex)
        {
            Console.WriteLine($"Ошибка при отмене бронирования: {ex.Message}");
            Console.WriteLine($"Трассировка стека: {ex.StackTrace}");
        }
    }
    private static void EditOrder(User user)
    {
        Console.WriteLine("Редактирование заказа (добавление услуги):");

        // Получение GuestId по UserId
        int guestId = _guestService.GetGuestIdByUserId(user.Id);
        if (guestId == 0)
        {
            Console.WriteLine("Ошибка: пользователь не зарегистрирован как гость.");
            return;
        }

        // Получение ID брони
        Console.WriteLine("Введите ID брони, для которой хотите редактировать заказ:");
        int reservationId = int.Parse(Console.ReadLine());

        // Получаем информацию о бронировании, чтобы извлечь GuestId
        var reservation = _reservationService.GetReservationById(reservationId);
        if (reservation == null)
        {
            Console.WriteLine("Ошибка: бронь не найдена.");
            return;
        }

        // Проверка, что пользователь является владельцем бронирования
        if (reservation.GuestId != guestId)
        {
            Console.WriteLine("Ошибка: вы не можете редактировать заказ, который не принадлежит вам.");
            return;
        }

        // Проверка, существует ли заказ для этого бронирования
        var existingOrder = _orderService.GetOrderByReservationId(reservationId);
        if (existingOrder == null)
        {
            Console.WriteLine("Ошибка: заказ для этого бронирования не найден.");
            return;
        }

        // Вывод текущей стоимости заказа перед редактированием
        Console.WriteLine($"Текущая стоимость заказа: {existingOrder.Cost} руб.");

        // Получаем доступные услуги
        var availableServices = _serviceService.GetAllServices();
        if (availableServices.Count == 0)
        {
            Console.WriteLine("Нет доступных услуг.");
            return;
        }

        Console.WriteLine("Доступные услуги:");
        for (int i = 0; i < availableServices.Count; i++)
        {
            Console.WriteLine($"{i + 1}. {availableServices[i].Name} - {availableServices[i].Cost} руб.");
        }

        // Выбор услуги
        Console.WriteLine("Выберите услугу (номер):");
        int serviceIndex = int.Parse(Console.ReadLine()) - 1;
        if (serviceIndex < 0 || serviceIndex >= availableServices.Count)
        {
            Console.WriteLine("Некорректный выбор.");
            return;
        }

        // Ввод количества
        Console.WriteLine("Введите количество:");
        int quantity = int.Parse(Console.ReadLine());

        // Получаем выбранную услугу
        var selectedService = availableServices[serviceIndex];

        // Создание нового объекта для добавления услуги в заказ
        var serviceInOrder = new ServiceInOrder
        {
            ServiceId = selectedService.Id,
            OrderId = existingOrder.Id,
            EmployeeId = user.Id,
            Amount = quantity
        };

        // Добавляем услугу в заказ
        _serviceInOrderService.AddServiceToOrder(serviceInOrder);

        // Пересчитываем стоимость заказа
        _orderService.RecalculateOrderCost(existingOrder.Id);

        // Получаем новую стоимость заказа после пересчета
        var updatedOrder = _orderService.GetOrderById(existingOrder.Id);
        //var notification = new Notification
        //{
        //    NotificationDateTime = DateTime.Now,
        //    NotificationText = $"Услуга '{selectedService.Name}' добавлена в ваш заказ.",
        //    OrderId = existingOrder.Id // Указываем OrderId из существующего заказа
        //};
        //_notificationService.CreateNotification(notification); // Передаем объект с OrderId
        // Выводим новую стоимость
        Console.WriteLine($"Новая стоимость заказа после пересчета: {updatedOrder.Cost} руб.");

        Console.WriteLine("Услуга успешно добавлена в заказ и стоимость пересчитана!");
    }

}
