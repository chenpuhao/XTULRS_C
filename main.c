/**
 * 图书馆预约系统
 * @author 陈朴浩
 * @date 2025/05/05
**/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cJSON.h"

//座位的链表
typedef struct Seats {
    int room;
    int seat;
    int isOccupied;
    struct Seats* next;
} Seat;

//用户的链表
typedef struct User {
    char* name;
    char* email;
    char* password;
    int isAdmin;
    char* seat;
    struct User* next;
} User;

//统计的链表
typedef struct Statistics {
    int room;
    int seat;
    time_t* time;
    char* user;
    struct Statistics* next;
} Statistic;

/**
 * 返回一个新的座位链表头指针
 * @return 新的座位链表头指针
 */
__declspec(dllexport) Seat** getSeatHead() {
    Seat** head = malloc(sizeof(Seat*));
    *head = NULL;
    return head;
}


/**
 *添加一个新的座位
 * @param head Seat链表头指针
 * @param room 房间号
 * @param seat 座位号
 * @param isOccupied 是否被占用
 * @return 0表示成功，-1表示失败(内存不足)
 */
__declspec(dllexport) int addSeat(Seat** head, const int room, const int seat, const int isOccupied) {
    if (head == NULL) {
        return -1;
    }
    Seat* temp = *head;
    while (temp != NULL) {
        if (temp->room == room && temp->seat == seat) {
            return -1;
        }
        temp = temp->next;
    }

    Seat* newSeat = malloc(sizeof(Seat));
    if (!newSeat) {
        return -1;
    }
    newSeat->room = room;
    newSeat->seat = seat;
    newSeat->isOccupied = isOccupied;
    newSeat->next = NULL;

    if (*head == NULL) {
        *head = newSeat;
    } else {
        temp = *head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newSeat;
    }
    return 0;
}

/**
 * 删除一个座位
 * @param head Seat链表头指针
 * @param room 房间号
 * @param seat 座位号
 * @return 0表示成功，-1表示失败(座位不存在或链表为空)
 */
__declspec(dllexport) int removeSeat(Seat** head, const int room, const int seat) {
    if (head == NULL || *head == NULL) {
        return -1;
    }
    Seat* temp = *head;
    Seat* prev = NULL;
    while (temp != NULL && (temp->room != room || temp->seat != seat)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return -1;
    }
    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    return 0;
}

/**
 * 通过房间号查找座位
 * @param head Seat链表头指针
 * @param room 房间号
 * @return NULL表示未找到，返回JSON格式的字符串
 */
__declspec(dllexport) char* findSeatByRoom(Seat** head, const int room) {
    if (head == NULL || *head == NULL) {
        return NULL;
    }
    cJSON* seatsArray = cJSON_CreateArray();
    if (!seatsArray) {
        return NULL;
    }
    const Seat* temp = *head;
    while (temp != NULL) {
        if (temp->room == room) {
            cJSON* seatObject = cJSON_CreateObject();
            if (!seatObject) {
                cJSON_Delete(seatsArray);
                return NULL;
            }
            cJSON_AddNumberToObject(seatObject, "room", temp->room);
            cJSON_AddNumberToObject(seatObject, "seat", temp->seat);
            cJSON_AddNumberToObject(seatObject, "isOccupied", temp->isOccupied);
            cJSON_AddItemToArray(seatsArray, seatObject);
        }
        temp = temp->next;
    }
    char* jsonString = cJSON_PrintUnformatted(seatsArray);
    cJSON_Delete(seatsArray);
    if (!jsonString) {
        return NULL;
    }
    return jsonString;
}

/**
 * 通过座位号查找座位
 * @param head Seat链表头指针
 * @param seat 座位号
 * @return NULL表示未找到，返回JSON格式的字符串
 */
__declspec(dllexport) char* findSeatBySeat(Seat** head, const int seat) {
    if (head == NULL || *head == NULL) {
        return NULL;
    }
    cJSON* seatsArray = cJSON_CreateArray();
    if (!seatsArray) {
        return NULL;
    }
    const Seat* temp = *head;
    while (temp != NULL) {
        if (temp->seat == seat) {
            cJSON* seatObject = cJSON_CreateObject();
            if (!seatObject) {
                cJSON_Delete(seatsArray);
                return NULL;
            }
            cJSON_AddNumberToObject(seatObject, "room", temp->room);
            cJSON_AddNumberToObject(seatObject, "seat", temp->seat);
            cJSON_AddNumberToObject(seatObject, "isOccupied", temp->isOccupied);
            cJSON_AddItemToArray(seatsArray, seatObject);
        }
        temp = temp->next;
    }
    char* jsonString = cJSON_PrintUnformatted(seatsArray);
    cJSON_Delete(seatsArray);
    if (!jsonString) {
        return NULL;
    }
    return jsonString;
}

/**
 * 通过是否被预约查找座位
 * @param head Seat链表头指针
 * @param isOccupied 是否被预约
 * @return NULL表示未找到，返回JSON格式的字符串
 */
__declspec(dllexport) char* findSeatByIsOccupied(Seat** head, const int isOccupied) {
    if (head == NULL || *head == NULL) {
        return NULL;
    }
    cJSON* seatsArray = cJSON_CreateArray();
    if (!seatsArray) {
        return NULL;
    }
    const Seat* temp = *head;
    while (temp != NULL) {
        if (temp->isOccupied == isOccupied) {
            cJSON* seatObject = cJSON_CreateObject();
            if (!seatObject) {
                cJSON_Delete(seatsArray);
                return NULL;
            }
            cJSON_AddNumberToObject(seatObject, "room", temp->room);
            cJSON_AddNumberToObject(seatObject, "seat", temp->seat);
            cJSON_AddNumberToObject(seatObject, "isOccupied", temp->isOccupied);
            cJSON_AddItemToArray(seatsArray, seatObject);
        }
        temp = temp->next;
    }
    char* jsonString = cJSON_PrintUnformatted(seatsArray);
    cJSON_Delete(seatsArray);
    if (!jsonString) {
        return NULL;
    }
    return jsonString;
}

/**
 * 返回所有座位信息
 * @param head Seat链表头指针
 * @return NULL表示未找到，返回JSON格式的字符串
 */
__declspec(dllexport) char* returnAllSeats(Seat** head) {
    if (head == NULL || *head == NULL) {
        return strdup("[]");
    }
    cJSON* seatsArray = cJSON_CreateArray();
    if (!seatsArray) {
        return NULL;
    }
    const Seat* temp = *head;
    while (temp != NULL) {
        cJSON* seatObject = cJSON_CreateObject();
        if (!seatObject) {
            cJSON_Delete(seatsArray);
            return NULL;
        }
        cJSON_AddNumberToObject(seatObject, "room", temp->room);
        cJSON_AddNumberToObject(seatObject, "seat", temp->seat);
        cJSON_AddNumberToObject(seatObject, "isOccupied", temp->isOccupied);
        cJSON_AddItemToArray(seatsArray, seatObject);
        temp = temp->next;
    }
    char* jsonString = cJSON_PrintUnformatted(seatsArray);
    cJSON_Delete(seatsArray);
    return jsonString;
}

/**
 * 释放座位链表
 * @param head Seat链表头指针
 */
__declspec(dllexport) void freeSeat(Seat** head) {
    Seat* temp = *head;
    while (temp != NULL) {
        Seat* next = temp->next;
        free(temp);
        temp = next;
    }
}

/**
 * 返回一个新的用户链表头指针
 * @return 新的用户链表头指针
 */
__declspec(dllexport) User** getUserHead() {
    User** head = malloc(sizeof(User*));
    *head = NULL;
    return head;
}

/**
 * 新增一个用户
 * @param user 用户链表头指针
 * @param name 用户名
 * @param email 邮箱
 * @param password 密码
 * @param isAdmin 是否为管理员
 * @param seat 座位号
 * @return 0表示成功，-1表示失败(内存不足)
 */
__declspec(dllexport) int addUser(User** user, const char* name, const char* email, const char* password, const int isAdmin, char* seat) {
    if (user == NULL || name == NULL || email == NULL || password == NULL || (isAdmin != 0 && isAdmin != 1)) {
        return -1;
    }

    User* temp = *user;
    while (temp != NULL) {
        if (strcmp(temp->email, email) == 0) {
            return -1;
        }
        temp = temp->next;
    }

    User* newUser = malloc(sizeof(User));
    if (!newUser) {
        return -1;
    }

    newUser->name = strdup(name);
    newUser->email = strdup(email);
    newUser->password = strdup(password);
    newUser->isAdmin = isAdmin;
    newUser->seat = seat;
    newUser->next = NULL;

    if (!newUser->name || !newUser->email || !newUser->password) {
        free(newUser->name);
        free(newUser->email);
        free(newUser->password);
        free(newUser);
        return -1;
    }

    if (*user == NULL) {
        *user = newUser;
    } else {
        temp = *user;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newUser;
    }

    return 0;
}

/**
 * 删除用户
 * @param user User链表头指针
 * @param email 用户邮箱
 * @param password 用户密码
 * @return 0表示成功，-1表示失败(用户不存在或链表为空)
 */
__declspec(dllexport) int deleteUser(User** user, const char* email, const char* password) {
    if (user == NULL || *user == NULL || email == NULL || password == NULL) {
        return -1;
    }
    User* temp = *user;
    User* prev = NULL;
    while (temp != NULL && (strcmp(temp->email, email) != 0 || strcmp(temp->password, password) != 0)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return -1;
    }
    if (prev == NULL) {
        *user = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp->name);
    free(temp->email);
    free(temp->password);
    free(temp);
    return 0;
}

/**
 * 返回所有用户
 * @param user 用户链表头指针
 * @param email 用户邮箱
 * @return NULL表示未找到或者不是管理员，返回JSON格式的字符串
 */
    __declspec(dllexport) char* returnAllUser(User** user, const char* email) {
    if (user == NULL || *user == NULL || email == NULL) {
        return NULL;
    }
    const User* current = *user;
    while (current != NULL) {
        if (strcmp(current->email, email) == 0) {
            if (!current->isAdmin) {
                return NULL;
            }
            break;
        }
        current = current->next;
    }
    cJSON* usersArray = cJSON_CreateArray();
    if (!usersArray) {
        return NULL;
    }
    const User* temp = *user;
    while (temp != NULL) {
        cJSON* userObject = cJSON_CreateObject();
        if (!userObject) {
            cJSON_Delete(usersArray);
            return NULL;
        }
        cJSON_AddStringToObject(userObject, "name", temp->name);
        cJSON_AddStringToObject(userObject, "email", temp->email);
        cJSON_AddNumberToObject(userObject, "isAdmin", temp->isAdmin);
        cJSON_AddItemToArray(usersArray, userObject);
        temp = temp->next;
    }
    char* jsonString = cJSON_PrintUnformatted(usersArray);
    cJSON_Delete(usersArray);
    if (!jsonString) {
        return NULL;
    }
    return jsonString;
}

/**
 * 修改用户名
 * @param user 用户链表头指针
 * @param name 用户名
 * @param email 邮箱
 * @return 0表示成功，-1表示失败(用户不存在或链表为空)
 */
__declspec(dllexport) int changeUsername(User** user, const char* name, const char* email) {
    if (user == NULL || name == NULL || email == NULL) {
        return -1;
    }
    User* temp = *user;
    while (temp != NULL) {
        if (strcmp(temp->email, email) == 0) {
            free(temp->name);
            temp->name = strdup(name);
            return 0;
        }
        temp = temp->next;
    }
    return -1;
}

/**
 * 修改密码
 * @param user 用户链表头指针
 * @param email 用户邮箱
 * @param password 用户密码
 * @return 0表示成功，-1表示失败(用户不存在或链表为空)
 */
__declspec(dllexport) int changePassword(User* user, const char* email, const char* password) {
    if (user == NULL || password == NULL || email == NULL) {
        return -1;
    }
    User* temp = user;
    while (temp != NULL) {
        if (strcmp(temp->email, email) == 0) {
            char* newPassword = strdup(password);
            if (!newPassword) {
                return -1; // 内存分配失败
            }
            free(temp->password);
            temp->password = newPassword;
            return 0;
        }
        temp = temp->next;
    }
    return -1;
}

/**
 * 释放用户链表
 * @param user 用户链表头指针
 */
__declspec(dllexport) void freeUser(User** user) {
    User* temp = *user;
    while (temp != NULL) {
        User* next = temp->next;
        free(temp->name);
        free(temp->email);
        free(temp->password);
        free(temp);
        temp = next;
    }
}

/**
 * 返回一个新的统计链表头指针
 * @return 新的统计链表头指针
 */
__declspec(dllexport) Statistic** getStatisticHead() {
    Statistic** head = malloc(sizeof(Statistic*));
    *head = NULL;
    return head;
}

/**
 * 添加一个新的统计节点
 * @param head Statistic链表头指针
 * @param room 房间号
 * @param seat 座位号
 * @param time 时间
 * @param user 用户
 * @return 0表示成功，-1表示失败
 */
__declspec(dllexport) int addStatistic(Statistic** head, const int room, const int seat, const time_t time, const char* user) {
    if (head == NULL || user == NULL) {
        return -1;
    }

    Statistic* temp = malloc(sizeof(Statistic));
    if (!temp) {
        return -1;
    }

    temp->room = room;
    temp->seat = seat;
    temp->time = malloc(sizeof(time_t));
    if (!temp->time) {
        free(temp);
        return -1;
    }
    *temp->time = time;

    temp->user = strdup(user);
    if (!temp->user) {
        free(temp->time);
        free(temp);
        return -1;
    }

    temp->next = NULL;
    if (*head == NULL) {
        *head = temp;
    } else {
        Statistic* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
    }

    return 0;
}

/**
 * 删除一个统计节点
 * @param head Statistic链表头指针
 * @param room 房间号
 * @param seat 座位号
 * @param time 时间
 * @return 0表示成功，-1表示失败(统计节点不存在或链表为空)
 */
__declspec(dllexport) int deleteStatistic(Statistic** head, const int room, const int seat, const time_t time) {
    if (head == NULL || *head == NULL) {
        return -1;
    }
    Statistic* temp = *head;
    Statistic* prev = NULL;
    while (temp != NULL && (temp->room != room || temp->seat != seat || *temp->time != time)) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        return -1;
    }
    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp->time);
    free(temp->user);
    free(temp);
    return 0;
}

/**
 * 返回所有统计信息
 * @param head Statistic链表头指针
 * @param user 用户链表头指针
 * @return NULL表示未找到，返回JSON格式的字符串
 */
__declspec(dllexport) char* returnAllStatistic(Statistic** head, User** user) {
    if (head == NULL || *head == NULL || user == NULL || *user == NULL) {
        return NULL;
    }

    const User* currentUser = *user;
    if (!currentUser->isAdmin) {
        return NULL;
    }

    cJSON* statisticsArray = cJSON_CreateArray();
    if (!statisticsArray) {
        return NULL;
    }
    const Statistic* temp = *head;
    while (temp != NULL) {
        cJSON* statisticObject = cJSON_CreateObject();
        if (!statisticObject) {
            cJSON_Delete(statisticsArray);
            return NULL;
        }
        cJSON_AddNumberToObject(statisticObject, "room", temp->room);
        cJSON_AddNumberToObject(statisticObject, "seat", temp->seat);
        char timeStr[64];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(temp->time));
        cJSON_AddStringToObject(statisticObject, "time", timeStr);
        cJSON_AddStringToObject(statisticObject, "user", temp->user);
        cJSON_AddItemToArray(statisticsArray, statisticObject);
        temp = temp->next;
    }
    char* jsonString = cJSON_PrintUnformatted(statisticsArray);
    cJSON_Delete(statisticsArray);
    if (!jsonString) {
        return NULL;
    }
    return jsonString;
}
/**
 * 释放统计链表
 * @param head Statistic链表头指针
 */
__declspec(dllexport) void freeStatistic(Statistic** head) {
    Statistic* temp = *head;
    while (temp != NULL) {
        Statistic* next = temp->next;
        free(temp->time);
        free(temp->user);
        free(temp);
        temp = next;
    }
}

/**
 * 保存座位信息到文件
 * @param head Seat链表头指针
 * @return 0表示成功，-1表示失败
 */
__declspec(dllexport) int saveSeats(Seat** head) {
    if (head == NULL) {
        return -1;
    }
    cJSON* root = cJSON_CreateObject();
    if (!root) {
        return -1;
    }
    cJSON* seatsArray = cJSON_CreateArray();
    if (!seatsArray) {
        cJSON_Delete(root);
        return -1;
    }
    cJSON_AddItemToObject(root, "seats", seatsArray);
    const Seat* temp = *head;
    while (temp != NULL) {
        cJSON* seatObject = cJSON_CreateObject();
        if (!seatObject) {
            cJSON_Delete(root);
            return -1;
        }
        cJSON_AddNumberToObject(seatObject, "room", temp->room);
        cJSON_AddNumberToObject(seatObject, "seat", temp->seat);
        cJSON_AddNumberToObject(seatObject, "isOccupied", temp->isOccupied);

        cJSON_AddItemToArray(seatsArray, seatObject);
        temp = temp->next;
    }
    char* jsonString = cJSON_Print(root);
    cJSON_Delete(root);
    if (!jsonString) {
        return -1;
    }
    FILE* file = fopen("seats.json", "w");
    if (!file) {
        free(jsonString);
        return -1;
    }
    fprintf(file, "%s", jsonString);
    fclose(file);
    free(jsonString);
    return 0;
}
/**
 * 保存用户信息到文件
 * @param user 用户链表头指针
 * @return 0表示成功，-1表示失败
 */
__declspec(dllexport) int saveUser(User** user) {
    if (user == NULL) {
        return -1;
    }
    cJSON* root = cJSON_CreateObject();
    if (!root) {
        return -1;
    }
    cJSON* usersArray = cJSON_CreateArray();
    if (!usersArray) {
        cJSON_Delete(root);
        return -1;
    }
    cJSON_AddItemToObject(root, "users", usersArray);
    const User* temp = *user;
    while (temp != NULL) {
        cJSON* userObject = cJSON_CreateObject();
        if (!userObject) {
            cJSON_Delete(root);
            return -1;
        }
        cJSON_AddStringToObject(userObject, "name", temp->name);
        cJSON_AddStringToObject(userObject, "email", temp->email);
        cJSON_AddStringToObject(userObject, "password", temp->password);
        cJSON_AddNumberToObject(userObject, "isAdmin", temp->isAdmin);
        if (temp->seat != NULL) {
            cJSON_AddStringToObject(userObject, "seat", temp->seat);
        } else {
            cJSON_AddNullToObject(userObject, "seat");
        }
        cJSON_AddItemToArray(usersArray, userObject);
        temp = temp->next;
    }
    char* jsonString = cJSON_Print(root);
    cJSON_Delete(root);
    if (!jsonString) {
        return -1;
    }
    FILE* file = fopen("users.json", "w");
    if (!file) {
        free(jsonString);
        return -1;
    }
    fprintf(file, "%s", jsonString);
    fclose(file);
    free(jsonString);
    return 0;
}

/**
 * 保存统计信息到文件
 * @param head Statistic链表头指针
 * @return 0表示成功，-1表示失败
 */
__declspec(dllexport) int saveStatistic(Statistic** head) {
    if (head == NULL) {
        return -1;
    }
    cJSON* root = cJSON_CreateObject();
    if (!root) {
        return -1;
    }
    cJSON* statisticsArray = cJSON_CreateArray();
    if (!statisticsArray) {
        cJSON_Delete(root);
        return -1;
    }
    cJSON_AddItemToObject(root, "statistics", statisticsArray);
    const Statistic* temp = *head;
    while (temp != NULL) {
        cJSON* statisticObject = cJSON_CreateObject();
        if (!statisticObject) {
            cJSON_Delete(root);
            return -1;
        }
        cJSON_AddNumberToObject(statisticObject, "room", temp->room);
        cJSON_AddNumberToObject(statisticObject, "seat", temp->seat);
        char timeStr[64];
        strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(temp->time));
        cJSON_AddStringToObject(statisticObject, "time", timeStr);
        cJSON_AddStringToObject(statisticObject, "user", temp->user);
        cJSON_AddItemToArray(statisticsArray, statisticObject);
        temp = temp->next;
    }
    char* jsonString = cJSON_Print(root);
    cJSON_Delete(root);
    if (!jsonString) {
        return -1;
    }
    FILE* file = fopen("statistics.json", "w");
    if (!file) {
        free(jsonString);
        return -1;
    }
    fprintf(file, "%s", jsonString);
    fclose(file);
    free(jsonString);
    return 0;
}

/**
 * 从文件加载座位信息
 * @param head Seat链表头指针
 * @return 0表示成功，-1表示失败
 */
__declspec(dllexport) int loadSeat(Seat** head) {
    if (head == NULL) {
        return -1;
    }
    FILE* file = fopen("seats.json", "r");
    if (!file) {
        return -1;
    }
    fseek(file, 0, SEEK_END);
    const long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(fileSize + 1);
    if (!buffer) {
        fclose(file);
        return -1;
    }
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);
    cJSON* root = cJSON_Parse(buffer);
    free(buffer);
    if (!root) {
        return -1;
    }
    const cJSON* seatsArray = cJSON_GetObjectItem(root, "seats");
    if (!cJSON_IsArray(seatsArray)) {
        cJSON_Delete(root);
        return -1;
    }
    cJSON* seatItem;
    cJSON_ArrayForEach(seatItem, seatsArray) {
        const cJSON* room = cJSON_GetObjectItem(seatItem, "room");
        const cJSON* seat = cJSON_GetObjectItem(seatItem, "seat");
        const cJSON* isOccupied = cJSON_GetObjectItem(seatItem, "isOccupied");
        if (!cJSON_IsNumber(room) || !cJSON_IsNumber(seat) || !cJSON_IsNumber(isOccupied)) {
            continue;
        }
        addSeat(head, room->valueint, seat->valueint, isOccupied->valueint);
    }
    cJSON_Delete(root);
    return 0;
}

/**
 * 从文件加载用户信息
 * @param user 用户链表头指针
 * @return 0表示成功，-1表示失败
 */
__declspec(dllexport) int loadUser(User** user) {
    if (user == NULL) {
        return -1;
    }
    FILE* file = fopen("users.json", "r");
    if (!file) {
        return -1;
    }
    fseek(file, 0, SEEK_END);
    const long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(fileSize + 1);
    if (!buffer) {
        fclose(file);
        return -1;
    }
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);

    cJSON* root = cJSON_Parse(buffer);
    free(buffer);
    if (!root) {
        return -1;
    }

    const cJSON* usersArray = cJSON_GetObjectItem(root, "users");
    if (!cJSON_IsArray(usersArray)) {
        cJSON_Delete(root);
        return -1;
    }

    cJSON* userItem;
    cJSON_ArrayForEach(userItem, usersArray) {
        const cJSON* name = cJSON_GetObjectItem(userItem, "name");
        const cJSON* email = cJSON_GetObjectItem(userItem, "email");
        const cJSON* password = cJSON_GetObjectItem(userItem, "password");
        const cJSON* isAdmin = cJSON_GetObjectItem(userItem, "isAdmin");
        const cJSON* seat = cJSON_GetObjectItem(userItem, "seat");

        if (!cJSON_IsString(name) || !cJSON_IsString(email) || !cJSON_IsString(password) || !cJSON_IsNumber(isAdmin)) {
            continue;
        }

        char* seatValue = cJSON_IsString(seat) ? seat->valuestring : NULL;
        if (addUser(user, name->valuestring, email->valuestring, password->valuestring, isAdmin->valueint, seatValue) == -1) {
            cJSON_Delete(root);
            return -1;
        }
    }

    cJSON_Delete(root);
    return 0;
}

/**
 * 从文件加载统计信息
 * @param head Statistic链表头指针
 * @return 0表示成功，-1表示失败
 */
__declspec(dllexport) int loadStatistic(Statistic** head) {
    if (head == NULL) {
        return -1;
    }
    FILE* file = fopen("statistics.json", "r");
    if (!file) {
        return -1;
    }
    fseek(file, 0, SEEK_END);
    const long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);
    char* buffer = malloc(fileSize + 1);
    if (!buffer) {
        fclose(file);
        return -1;
    }
    fread(buffer, 1, fileSize, file);
    buffer[fileSize] = '\0';
    fclose(file);
    cJSON* root = cJSON_Parse(buffer);
    free(buffer);
    if (!root) {
        return -1;
    }
    const cJSON* statisticsArray = cJSON_GetObjectItem(root, "statistics");
    if (!cJSON_IsArray(statisticsArray)) {
        cJSON_Delete(root);
        return -1;
    }
    cJSON* statisticItem;
    cJSON_ArrayForEach(statisticItem, statisticsArray) {
        const cJSON* room = cJSON_GetObjectItem(statisticItem, "room");
        const cJSON* seat = cJSON_GetObjectItem(statisticItem, "seat");
        const cJSON* time = cJSON_GetObjectItem(statisticItem, "time");
        const cJSON* user = cJSON_GetObjectItem(statisticItem, "user");
        if (!cJSON_IsNumber(room) || !cJSON_IsNumber(seat) || !cJSON_IsString(time) || !cJSON_IsString(user)) {
            continue;
        }
        struct tm tm = {0};
        if (sscanf(time->valuestring, "%d-%d-%d %d:%d:%d",
                   &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
                   &tm.tm_hour, &tm.tm_min, &tm.tm_sec) == 6) {
            tm.tm_year -= 1900;
            tm.tm_mon -= 1;
            const time_t timestamp = mktime(&tm);
            addStatistic(head, room->valueint, seat->valueint, timestamp, user->valuestring);
        }
    }
    cJSON_Delete(root);
    return 0;
}

/**
 * 登录
 * @param user 用户链表头指针
 * @param email 邮箱
 * @param password 密码
 * @return 用户指针
 */
__declspec(dllexport) User* login(User** user, const char* email, const char* password) {
    if (user == NULL || *user == NULL || email == NULL || password == NULL) {
        return NULL;
    }
    User* temp = *user;
    while (temp != NULL) {
        if (strcmp(temp->email, email) == 0 && strcmp(temp->password, password) == 0) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

/**
 * 预约座位
 * @param head Seat链表头指针
 * @param room 房间号
 * @param seat 座位号
 * @param user 用户指针
 * @param statistic 统计链表头指针
 * @return 0表示成功，-1表示失败(座位已被预约或用户不存在)
 */
__declspec(dllexport) int reserveSeat(Seat** head,const int room, const int seat, User* user,Statistic* statistic) {
    if (user->seat != NULL) {
        return -1;
    }
    Seat* temp = *head;
    while (temp != NULL) {
        if (temp->room == room && temp->seat == seat) {
            if (temp->isOccupied) {
                return -1;
            }
            temp->isOccupied = 1;
            user->seat = malloc(128);
            if (!user->seat) {
                return -1;
            }
            snprintf(user->seat, 128, "{\"room\":%d,\"seat\":%d}", room, seat);
            addStatistic(&statistic, room, seat, time(NULL), user->name);
            return 0;
        }
        temp = temp->next;
    }
    return -1;
}
/**
 * 取消预约座位
 * @param head Seat链表头指针
 * @param room 房间号
 * @param seat 座位号
 * @param user 用户指针
 * @return 0表示成功，-1表示失败(座位未被预约或用户未预约座位)
 */
__declspec(dllexport) int cancelReservation(Seat** head,const int room, const int seat, User* user) {
    if (user->seat != NULL) {
        return -1;
    }
    Seat* temp = *head;
    while (temp != NULL) {
        if (temp->room == room && temp->seat == seat) {
            if (!temp->isOccupied) {
                return -1;
            }
            temp->isOccupied = 0;
            free(user->seat);
            user->seat = NULL;
            return 0;
        }
        temp = temp->next;
    }
    return -1;
}

/**
 * 测试函数
 * @return 0
 */
__declspec(dllexport) int test() {
    return 123;
}

