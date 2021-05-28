#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "MD5.h"
#include "cJSON.h"
//#include "sdk_dlog.h"
//#include "pachira_mem.h"
#include "RecordUserData.h"

#define RECORD_USER_DATA    "RECORD_USER_DATA"

RecordUserData::RecordUserData() {
    m_music = NULL;
    m_musicSize = 0;
    memset(m_musicCheckSum, 0, sizeof(m_musicCheckSum));

    m_phone = NULL;
    m_phoneSize = 0;
    memset(m_phoneCheckSum, 0, sizeof(m_phoneCheckSum));

    m_phoneHistory = NULL;
    m_phoneHistorySize = 0;
    memset(m_phoneHistoryCheckSum, 0, sizeof(m_phoneHistoryCheckSum));

    m_userData = NULL;
    m_userDataSize = 0;
}

RecordUserData::~RecordUserData() { 
    if(m_music) {
        free(m_music);
        m_music = NULL;
    }

    if(m_phone) {
        free(m_phone);
        m_phone = NULL;
    }

    if(m_phoneHistory) {
        free(m_phoneHistory);
        m_phoneHistory = NULL;
    }

    if(m_userData) {
        free(m_userData);
        m_userData = NULL;
    }
}

int RecordUserData::setUserData(const char *info) {
    if(NULL == info) {
        printf( "input info is null");
        return -1;
    }
    cJSON *jUserInfo = cJSON_Parse(info);
    if(NULL == jUserInfo) {
        printf( "cjson parse fail");
        return -1;
    }

    MD5 md5;
    char *content = NULL;
    int contentLen = 0;
    char *md5Value = NULL;
    
    cJSON *jMusic = cJSON_ChainSearch(jUserInfo, "music");
    if(jMusic) {
        content = cJSON_PrintUnformatted(jMusic);
        md5Value = md5.getMD5(content);
        if(strcasecmp(md5Value, m_musicCheckSum) != 0) {
            contentLen = strlen(content);
            if(contentLen >= m_musicSize) {
                contentLen += 20;
                char *music = (char *)realloc(m_music, contentLen);       
                if(NULL == music) {
                    printf( "realloc fail");
                    cJSON_Delete(jUserInfo);
                    return -1;
                }
                m_musicSize = contentLen;
                m_music = music;
            }
            strncpy(m_music, content, m_musicSize);
            strncpy(m_musicCheckSum, md5Value, sizeof(m_musicCheckSum));
        }
        free(content);
    }
   
    cJSON *jPhone = cJSON_ChainSearch(jUserInfo, "phone");
    if(jPhone) {
        content = cJSON_PrintUnformatted(jPhone);
        md5Value = md5.getMD5(content);
        if(strcasecmp(md5Value, m_phoneCheckSum) != 0) {
            contentLen = strlen(content);
            if(contentLen >= m_phoneSize) {
                contentLen += 20;
                char *phone = (char *)realloc(m_phone, contentLen);       
                if(NULL == phone) {
                    printf( "realloc fail");
                    cJSON_Delete(jUserInfo);
                    return -1;
                }
                m_phoneSize = contentLen;
                m_phone = phone;
            }
            strncpy(m_phone, content, m_phoneSize);
            strncpy(m_phoneCheckSum, md5Value, sizeof(m_phoneCheckSum));
        }
        free(content);
    }
    
    cJSON *jPhoneHistory = cJSON_ChainSearch(jUserInfo, "phone_history");
    if(jPhoneHistory) {
        content = cJSON_PrintUnformatted(jPhoneHistory);
        md5Value = md5.getMD5(content);
        if(strcasecmp(md5Value, m_phoneHistoryCheckSum) != 0) {
            contentLen = strlen(content);
            if(contentLen >= m_phoneHistorySize) {
                contentLen += 20;
                char *phoneHistory = (char *)realloc(m_phoneHistory, contentLen);       
                if(NULL == phoneHistory) {
                    printf( "realloc fail");
                    cJSON_Delete(jUserInfo);
                    return -1;
                }
                m_phoneHistorySize = contentLen;
                m_phoneHistory = phoneHistory;
            }
            strncpy(m_phoneHistory, content, m_phoneHistorySize);
            strncpy(m_phoneHistoryCheckSum, md5Value, sizeof(m_phoneHistoryCheckSum));
        }
        free(content);
    }
    cJSON_Delete(jUserInfo);
    return 0;
}

const char* RecordUserData::getUserData() {
    cJSON *resultJson = cJSON_CreateObject(); 
    if(NULL == resultJson) {
        return NULL;
    }
    
    cJSON *jItem = NULL;
    if(m_music) {
        jItem = cJSON_Parse(m_music);
        if(jItem) {
            cJSON_AddItemToObject(resultJson, "music", jItem);
        } else {
            printf( "m_music parse error");
        }
    }
    if(m_phone) {
        jItem = cJSON_Parse(m_phone);
        if(jItem) {
            cJSON_AddItemToObject(resultJson, "phone", jItem);
        } else {
            printf( "m_phone parse error");
        }
    }
    if(m_phoneHistory) {
        jItem = cJSON_Parse(m_phoneHistory);
        if(jItem) {
            cJSON_AddItemToObject(resultJson, "phone_history", jItem);
        } else {
            printf( "m_phoneHistory parse error");
        }
    }
    
    char *resultStr = cJSON_PrintUnformatted(resultJson);
    if(NULL == resultStr) {
        printf( "resultStr is null");
        cJSON_Delete(resultJson);
        return NULL;
    }
    int resultStrLen = strlen(resultStr);
    if(resultStrLen >= m_userDataSize) {
        resultStrLen += 20;
        char *userData = (char *)realloc(m_userData, resultStrLen);
        if(NULL == userData) {
            printf( "realloc fail");
            free(resultStr);
            cJSON_Delete(resultJson);
            return NULL;
        }
        m_userDataSize = resultStrLen;
        m_userData = userData;
    }

    strncpy(m_userData, resultStr, m_userDataSize);

    free(resultStr);
    cJSON_Delete(resultJson);
    return m_userData;
}

