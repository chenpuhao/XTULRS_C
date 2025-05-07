/**
 * ͼ���ԤԼϵͳ
 * @author ���Ӻ�
 * @date 2025/05/05
**/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "cJSON.h"

//��λ������
typedef struct Seats {
    int room;
    int seat;
    int isOccupied;
    struct Seats* next;
} Seat;

//�û�������
typedef struct User {
    char* name;
    char* email;
    char* password;
    int isAdmin;
    char* seat;
    struct User* next;
} User;

//ͳ�Ƶ�����
typedef struct Statistics {
    int room;
    int seat;
    time_t* time;
    char* user;
    struct Statistics* next;
} Statistic;

/**
 * ����һ���µ���λ����ͷָ��
 * @return �µ���λ����ͷָ��
 */
__declspec(dllexport) Seat** getSeatHead() {
    Seat** head = malloc(sizeof(Seat*));
    *head = NULL;
    return head;
}


/**
 *���һ���µ���λ
 * @param head Seat����ͷָ��
 * @param room �����
 * @param seat ��λ��
 * @param isOccupied �Ƿ�ռ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��(�ڴ治��)
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
 * ɾ��һ����λ
 * @param head Seat����ͷָ��
 * @param room �����
 * @param seat ��λ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��(��λ�����ڻ�����Ϊ��)
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
 * ͨ������Ų�����λ
 * @param head Seat����ͷָ��
 * @param room �����
 * @return NULL��ʾδ�ҵ�������JSON��ʽ���ַ���
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
 * ͨ����λ�Ų�����λ
 * @param head Seat����ͷָ��
 * @param seat ��λ��
 * @return NULL��ʾδ�ҵ�������JSON��ʽ���ַ���
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
 * ͨ���Ƿ�ԤԼ������λ
 * @param head Seat����ͷָ��
 * @param isOccupied �Ƿ�ԤԼ
 * @return NULL��ʾδ�ҵ�������JSON��ʽ���ַ���
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
 * ����������λ��Ϣ
 * @param head Seat����ͷָ��
 * @return NULL��ʾδ�ҵ�������JSON��ʽ���ַ���
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
 * �ͷ���λ����
 * @param head Seat����ͷָ��
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
 * ����һ���µ��û�����ͷָ��
 * @return �µ��û�����ͷָ��
 */
__declspec(dllexport) User** getUserHead() {
    User** head = malloc(sizeof(User*));
    *head = NULL;
    return head;
}

/**
 * ����һ���û�
 * @param user �û�����ͷָ��
 * @param name �û���
 * @param email ����
 * @param password ����
 * @param isAdmin �Ƿ�Ϊ����Ա
 * @param seat ��λ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��(�ڴ治��)
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
    newUser->seat = strdup(seat);
    newUser->next = NULL;

    if (!newUser->name || !newUser->email || !newUser->password) {
        free(newUser->name);
        free(newUser->email);
        free(newUser->password);
        free(newUser->seat);
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
 * ɾ���û�
 * @param user User����ͷָ��
 * @param email �û�����
 * @param password �û�����
 * @return 0��ʾ�ɹ���-1��ʾʧ��(�û������ڻ�����Ϊ��)
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
 * ���������û�
 * @param user �û�����ͷָ��
 * @param email �û�����
 * @return NULL��ʾδ�ҵ����߲��ǹ���Ա������JSON��ʽ���ַ���
 */
__declspec(dllexport) char* returnAllUser(User** user, const char* email) {
    if (user == NULL || *user == NULL || email == NULL) {
        return NULL;
    }

    // ��֤�Ƿ�Ϊ����Ա�û�
    const User* current = *user;
    while (current != NULL) {
        if (strcmp(current->email, email) == 0) {
            if (!current->isAdmin) {
                return NULL; // �ǹ���Ա�û���Ȩ��
            }
            break;
        }
        current = current->next;
    }
    if (current == NULL) {
        return NULL; // δ�ҵ�ָ��������û�
    }

    // ���� JSON ����
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

        cJSON_AddStringToObject(userObject, "name", temp->name ? temp->name : "");
        cJSON_AddStringToObject(userObject, "email", temp->email ? temp->email : "");
        cJSON_AddNumberToObject(userObject, "isAdmin", temp->isAdmin);
        cJSON_AddStringToObject(userObject, "password", temp->password ? temp->password : "");
        cJSON_AddStringToObject(userObject, "seat", temp->seat ? temp->seat : "");

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
 * �޸��û���
 * @param user �û�����ͷָ��
 * @param name �û���
 * @param email ����
 * @return 0��ʾ�ɹ���-1��ʾʧ��(�û������ڻ�����Ϊ��)
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
 * �޸�����
 * @param user �û�����ͷָ��
 * @param email �û�����
 * @param password �û�����
 * @return 0��ʾ�ɹ���-1��ʾʧ��(�û������ڻ�����Ϊ��)
 */
__declspec(dllexport) int changePassword(User** user, const char* email, const char* password) {
    if (user == NULL || password == NULL || email == NULL) {
        return -1;
    }
    User* temp = *user;
    while (temp != NULL) {
        if (strcmp(temp->email, email) == 0) {
            free(temp->password);
            temp->password = strdup(password);
            return 0;
        }
        temp = temp->next;
    }
    return -1;
}

/**
 * �ͷ��û�����
 * @param user �û�����ͷָ��
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
 * ����һ���µ�ͳ������ͷָ��
 * @return �µ�ͳ������ͷָ��
 */
__declspec(dllexport) Statistic** getStatisticHead() {
    Statistic** head = malloc(sizeof(Statistic*));
    *head = NULL;
    return head;
}

/**
 * ���һ���µ�ͳ�ƽڵ�
 * @param head Statistic����ͷָ��
 * @param room �����
 * @param seat ��λ��
 * @param time ʱ��
 * @param user �û�
 * @return 0��ʾ�ɹ���-1��ʾʧ��
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
 * ɾ��һ��ͳ�ƽڵ�
 * @param head Statistic����ͷָ��
 * @param room �����
 * @param seat ��λ��
 * @param time ʱ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��(ͳ�ƽڵ㲻���ڻ�����Ϊ��)
 */
__declspec(dllexport) int deleteStatistic(Statistic** head, const int room, const int seat, const char* time) {
    if (head == NULL || *head == NULL || time == NULL) {
        return -1;
    }

    // ��ʱ���ַ�������Ϊ time_t
    struct tm tm = {0};
    if (sscanf(time, "%d-%d-%d %d:%d:%d",
               &tm.tm_year, &tm.tm_mon, &tm.tm_mday,
               &tm.tm_hour, &tm.tm_min, &tm.tm_sec) != 6) {
        return -1;
    }
    tm.tm_year -= 1900;
    tm.tm_mon -= 1;
    const time_t parsedTime = mktime(&tm);
    if (parsedTime == -1) {
        return -1;
    }

    Statistic* temp = *head;
    Statistic* prev = NULL;

    while (temp != NULL) {
        if (temp->room == room && temp->seat == seat && *temp->time == parsedTime) {
            if (prev == NULL) {
                *head = temp->next;
            } else {
                prev->next = temp->next;
            }
            free(temp->time);
            free(temp->user);
            free(temp);
            return 0; // ɾ���ɹ�
        }
        prev = temp;
        temp = temp->next;
    }

    return -1; // δ�ҵ�ƥ���ͳ����Ϣ
}

/**
 * ��������ͳ����Ϣ
 * @param head Statistic����ͷָ��
 * @param user �û�����ͷָ��
 * @return NULL��ʾδ�ҵ�������JSON��ʽ���ַ���
 */
__declspec(dllexport) char* returnAllStatistic(Statistic** head, User* user) {
    if (head == NULL || *head == NULL || user == NULL) {
        return NULL;
    }

    const User* currentUser = user;
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
 * ͨ������Ų���ͳ����Ϣ
 * @param head Statistic����ͷָ��
 * @param room �����
 * @return NULL��ʾδ�ҵ�������JSON��ʽ���ַ���
 */
__declspec(dllexport) char* findStatisticByRoom(Statistic** head, const int room) {
    if (head == NULL || *head == NULL) {
        return NULL;
    }
    cJSON* statisticsArray = cJSON_CreateArray();
    if (!statisticsArray) {
        return NULL;
    }
    const Statistic* temp = *head;
    while (temp != NULL) {
        if (temp->room == room) {
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
        }
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
 * ͨ����λ�Ų���ͳ����Ϣ
 * @param head Statistic����ͷָ��
 * @param seat ��λ��
 * @return NULL��ʾδ�ҵ�������JSON��ʽ���ַ���
 */
__declspec(dllexport) char* findStatisticBySeat(Statistic** head, const int seat) {
    if (head == NULL || *head == NULL) {
        return NULL;
    }
    cJSON* statisticsArray = cJSON_CreateArray();
    if (!statisticsArray) {
        return NULL;
    }
    const Statistic* temp = *head;
    while (temp != NULL) {
        if (temp->seat == seat) {
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
        }
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
 * ͨ��ʱ�����ͳ����Ϣ
 * @param head Statistic����ͷָ��
 * @param time ʱ��
 * @return NULL��ʾδ�ҵ�������JSON��ʽ���ַ���
 */
__declspec(dllexport) char* findStatisticByTime(Statistic** head, const char* time) {
    if (head == NULL || *head == NULL || time == NULL) {
        return NULL;
    }

    struct tm inputDate = {0};
    if (sscanf(time, "%4d-%2d-%2d", &inputDate.tm_year, &inputDate.tm_mon, &inputDate.tm_mday) != 3) {
        return NULL;
    }
    inputDate.tm_year -= 1900;
    inputDate.tm_mon -= 1;
    inputDate.tm_hour = 0;
    inputDate.tm_min = 0;
    inputDate.tm_sec = 0;
    time_t inputDayStart = mktime(&inputDate);
    if (inputDayStart == -1) {
        return NULL;
    }

    cJSON* statisticsArray = cJSON_CreateArray();
    if (!statisticsArray) {
        return NULL;
    }

    const Statistic* temp = *head;
    while (temp != NULL) {
        struct tm statDate;
        localtime_s(&statDate, temp->time);
        statDate.tm_hour = 0;
        statDate.tm_min = 0;
        statDate.tm_sec = 0;
        time_t statDayStart = mktime(&statDate);

        if (inputDayStart == statDayStart) {
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
        }
        temp = temp->next;
    }

    char* jsonString = cJSON_PrintUnformatted(statisticsArray);
    cJSON_Delete(statisticsArray);
    return jsonString;
}

/**
 * ͨ���û�����ͳ����Ϣ
 * @param head Statistic����ͷָ��
 * @param user �û���
 * @return NULL��ʾδ�ҵ�������JSON��ʽ���ַ���
 */
__declspec(dllexport) char* findStatisticByUser(Statistic** head, const char* user) {
    if (head == NULL || *head == NULL || user == NULL) {
        return NULL;
    }
    cJSON* statisticsArray = cJSON_CreateArray();
    if (!statisticsArray) {
        return NULL;
    }
    const Statistic* temp = *head;
    while (temp != NULL) {
        if (strcmp(temp->user, user) == 0) {
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
        }
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
 * �ͷ�ͳ������
 * @param head Statistic����ͷָ��
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
 * ������λ��Ϣ���ļ�
 * @param head Seat����ͷָ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��
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
 * �����û���Ϣ���ļ�
 * @param user �û�����ͷָ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��
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
 * ����ͳ����Ϣ���ļ�
 * @param head Statistic����ͷָ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��
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
 * ���ļ�������λ��Ϣ
 * @param head Seat����ͷָ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��
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
 * ���ļ������û���Ϣ
 * @param user �û�����ͷָ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��
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
        if (addUser(user, name->valuestring, email->valuestring, password->valuestring, isAdmin->valueint, seat->valuestring) == -1) {
            cJSON_Delete(root);
            return -1;
        }
    }

    cJSON_Delete(root);
    return 0;
}

/**
 * ���ļ�����ͳ����Ϣ
 * @param head Statistic����ͷָ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��
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
 * ��¼
 * @param user �û�����ͷָ��
 * @param email ����
 * @param password ����
 * @return �û�ָ��
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
 * ԤԼ��λ
 * @param head Seat����ͷָ��
 * @param room �����
 * @param seat ��λ��
 * @param user �û�ָ��
 * @param statistic ͳ������ͷָ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��(��λ�ѱ�ԤԼ���û�������)
 */
__declspec(dllexport) int reserveSeat(Seat** head, const int room, const int seat, User* user, Statistic** statistic) {
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
            user->seat = malloc(16);
            if (!user->seat) {
                return -1;
            }
             snprintf(user->seat, 128, "{\"room\":%d,\"seat\":%d}", room, seat);
            addStatistic(statistic, room, seat, time(NULL), user->name);
            return 0;
        }
        temp = temp->next;
    }
    return -1;
}

/**
 * ȡ��ԤԼ��λ
 * @param head Seat����ͷָ��
 * @param user �û�ָ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��(��λδ��ԤԼ���û�δԤԼ��λ)
 */
__declspec(dllexport) int cancelReservation(Seat** head, User* user) {
    if (user->seat == NULL) {
        return -1;
    }
    int room, seat;
    if (sscanf(user->seat, "{\"room\":%d,\"seat\":%d}", &room, &seat) != 2) {
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
 * ��ȡ�û���Ϣ
 * @param user �û�ָ��
 * @return JSON��ʽ���ַ���
 */
__declspec(dllexport) char* getUserInfo(const User* user) {
    if (user == NULL ) {
        return NULL;
    }
    const User* temp = user;
    cJSON* userObject = cJSON_CreateObject();
    if (!userObject) {
        return NULL;
    }
    cJSON_AddStringToObject(userObject, "name", temp->name);
    cJSON_AddStringToObject(userObject, "email", temp->email);
    cJSON_AddNumberToObject(userObject, "isAdmin", temp->isAdmin);
    cJSON_AddStringToObject(userObject, "seat", temp->seat ? temp->seat : "");
    char* jsonString = cJSON_PrintUnformatted(userObject);
    cJSON_Delete(userObject);
    return jsonString;
}

/**
 * ���û�����Ϊ����Ա
 * @param user �û�����ͷָ��
 * @param email �û�����
 * @return 0��ʾ�ɹ���-1��ʾʧ��(�û������ڻ�����Ϊ��)
 */
__declspec(dllexport) int setAsAdmin(User** user, const char* email) {
    if (user == NULL || email == NULL) {
        return -1;
    }
    User* temp = *user;
    while (temp != NULL) {
        if (strcmp(temp->email, email) == 0) {
            temp->isAdmin = 1;
            return 0;
        }
        temp = temp->next;
    }
    return -1;
}

/**
 * ���û�����Ϊ��ͨ�û�
 * @param user �û�����ͷָ��
 * @param email �û�����
 * @return 0��ʾ�ɹ���-1��ʾʧ��(�û������ڻ�����Ϊ��)
 */
__declspec(dllexport) int setAsUser(User** user, const char* email) {
    if (user == NULL || email == NULL) {
        return -1; // ������Ч
    }
    User* temp = *user;
    while (temp != NULL) {
        if (strcmp(temp->email, email) == 0) {
            temp->isAdmin = 0;
            return 0; // �ɹ�
        }
        temp = temp->next;
    }
    return -1; // δ�ҵ��û�
}

/**
 * ������λ��Ϣ
 * @param head Seat����ͷָ��
 * @param seatJson ��λ��Ϣ��JSON�ַ���
 * @return JSON��ʽ���ַ�����������ӳɹ���ʧ�ܵ�����
 */
__declspec(dllexport) char* importSeat(Seat** head, const char* seatJson) {
    if (head == NULL || seatJson == NULL) {
        return strdup("��ӳɹ�:0,���ʧ��:0,ԭ��:������Ч");
    }

    cJSON* root = cJSON_Parse(seatJson);
    if (!root) {
        return strdup("��ӳɹ�:0,���ʧ��:0,ԭ��:JSON����ʧ��");
    }

    const cJSON* seatsArray = cJSON_GetObjectItem(root, "seats");
    if (!cJSON_IsArray(seatsArray)) {
        cJSON_Delete(root);
        return strdup("��ӳɹ�:0,���ʧ��:0,ԭ��:JSON��ʽ����");
    }

    int successCount = 0;
    int failureCount = 0;

    cJSON* seatItem;
    cJSON_ArrayForEach(seatItem, seatsArray) {
        const cJSON* room = cJSON_GetObjectItem(seatItem, "room");
        const cJSON* seat = cJSON_GetObjectItem(seatItem, "seat");
        const cJSON* isOccupied = cJSON_GetObjectItem(seatItem, "isOccupied");
        if (!cJSON_IsNumber(room) || !cJSON_IsNumber(seat)|| !cJSON_IsNumber(isOccupied)) {
            failureCount++;
            continue;
        }

        const Seat* temp = *head;
        int exists = 0;
        while (temp != NULL) {
            if (temp->room == room->valueint && temp->seat == seat->valueint ) {
                exists = 1;
                break;
            }
            temp = temp->next;
        }

        if (exists) {
            failureCount++;
            continue;
        }

        if (addSeat(head, room->valueint, seat->valueint, isOccupied->valueint) == 0) {
            successCount++;
        } else {
            failureCount++;
        }
    }

    cJSON_Delete(root);

    char result[128];
    snprintf(result, sizeof(result), "��ӳɹ�:%d,���ʧ��:%d,ԭ��:%s",
             successCount, failureCount, failureCount > 0 ? "������λ�Ѵ��ڻ����ʧ��" : "��");

    return strdup(result);
}

/**
 * ������λ��Ϣ���ļ�
 * @param head Seat����ͷָ��
 * @param filePath �ļ�·��
 * @return 0��ʾ�ɹ���-1��ʾʧ��
 */
__declspec(dllexport) int exportSeat(Seat** head, const char* filePath) {
    if (head == NULL || filePath == NULL) {
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
    FILE* file = fopen(filePath, "w");
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
 * �����λԤԼ
 * @param head Seat����ͷָ��
 * @param room �����
 * @param seat ��λ��
 * @return 0��ʾ�ɹ���-1��ʾʧ��(��λδ��ԤԼ������Ϊ��)
 */
__declspec(dllexport) int cancelSeat(Seat** head, const int room, const int seat) {
    if (head == NULL) {
        return -1;
    }
    Seat* temp = *head;
    while (temp != NULL) {
        if (temp->room == room && temp->seat == seat) {
            temp->isOccupied = 0;
            return 0;
        }
        temp = temp->next;
    }
    return -1;
}

/**
 * �������ͳ����Ϣ
 * @param head Statistic����ͷָ��
 */
__declspec(dllexport) void clearAllStatistic(Statistic** head) {
    Statistic* temp = *head;
    while (temp != NULL) {
        Statistic* next = temp->next;
        free(temp->time);
        free(temp->user);
        free(temp);
        temp = next;
    }
    *head = NULL;
}
/**
 * ͨ��ʱ�䷶Χ����ͳ����Ϣ
 * @param head Statistic����ͷָ��
 * @param startTime ��ʼʱ��
 * @param endTime ����ʱ��
 * @return NULL��ʾδ�ҵ�������JSON��ʽ���ַ���
 */
__declspec(dllexport) char* findStatisticByTimeRange(Statistic** head, const char* startTime, const char* endTime) {
    if (head == NULL || *head == NULL || startTime == NULL || endTime == NULL) {
        return NULL;
    }

    struct tm startDate = {0};
    struct tm endDate = {0};
    if (sscanf(startTime, "%4d-%2d-%2d", &startDate.tm_year, &startDate.tm_mon, &startDate.tm_mday) != 3 ||
        sscanf(endTime, "%4d-%2d-%2d", &endDate.tm_year, &endDate.tm_mon, &endDate.tm_mday) != 3) {
        return NULL; // ʱ���ʽ����
    }
    startDate.tm_year -= 1900;
    startDate.tm_mon -= 1;
    startDate.tm_hour = 0;
    startDate.tm_min = 0;
    startDate.tm_sec = 0;
    time_t startDayStart = mktime(&startDate);
    if (startDayStart == -1) {
        return NULL; // ��ʼʱ�����ʧ��
    }

    endDate.tm_year -= 1900;
    endDate.tm_mon -= 1;
    endDate.tm_hour = 23;
    endDate.tm_min = 59;
    endDate.tm_sec = 59;
    time_t endDayEnd = mktime(&endDate);
    if (endDayEnd == -1) {
        return NULL; // ����ʱ�����ʧ��
    }

    cJSON* statisticsArray = cJSON_CreateArray();
    if (!statisticsArray) {
        return NULL; // JSON ����ʧ��
    }

    const Statistic* temp = *head;
    while (temp != NULL) {
        if (*temp->time >= startDayStart && *temp->time <= endDayEnd) {
            cJSON* statisticObject = cJSON_CreateObject();
            if (!statisticObject) {
                cJSON_Delete(statisticsArray);
                return NULL; // �ͷ��ѷ���� JSON ����
            }
            cJSON_AddNumberToObject(statisticObject, "room", temp->room);
            cJSON_AddNumberToObject(statisticObject, "seat", temp->seat);
            char timeStr[64];
            if (strftime(timeStr, sizeof(timeStr), "%Y-%m-%d %H:%M:%S", localtime(temp->time))) {
                cJSON_AddStringToObject(statisticObject, "time", timeStr);
            }
            cJSON_AddStringToObject(statisticObject, "user", temp->user);
            cJSON_AddItemToArray(statisticsArray, statisticObject);
        }
        temp = temp->next;
    }

    char* jsonString = cJSON_PrintUnformatted(statisticsArray);
    cJSON_Delete(statisticsArray);
    return jsonString;
}

/**
 * ���Ժ���
 * @return 0
 */
__declspec(dllexport) int test() {
    return 123;
}