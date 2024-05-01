#include "jsmn.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.c"
#include "http.c"

#define MAX_JSON_LENGTH 1000
int temp; 
char JSON_STRING[MAX_JSON_LENGTH];

int http_call(const char *JSON_STRING);
void clearInputBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

static int jsoneq(const char *json, jsmntok_t *tok, const char *s) {
  // printf("\ns==%s|strlen(s)==%d|tok->end - tok->start==%d\n",
  // s,(int)strlen(s),tok->end - tok->start);
  if (tok->type == JSMN_STRING && (int)strlen(s) == tok->end - tok->start &&
      strncmp(json + tok->start, s, tok->end - tok->start) == 0) {
    return 0;
  }
  return -1;
}

void jasmin_Parser() {
  int i;
  int r;
  jsmn_parser p;
  jsmntok_t t[128]; /* We expect no more than 128 tokens */

  jsmn_init(&p);
  r = jsmn_parse(&p, JSON_STRING, strlen(JSON_STRING), t,
                 sizeof(t) / sizeof(t[0]));
  if (r < 0) {
    printf("Failed to parse JSON: %d\n", r);
    return;
  }

  /* Assume the top-level element is an object */
  if (r < 1 || t[0].type != JSMN_OBJECT) {
    printf("Object expected\n");
    return;
  }

  // printf("Number of tookens found==%d",r);
  /* Loop over all keys of the root object */
  for (i = 1; i < r; i++) {
    if (jsoneq(JSON_STRING, &t[i], "username") == 0) {
      /* We may use strndup() to fetch string value */
      printf("\n-Username: %.*s\n", t[i + 1].end - t[i + 1].start,
             JSON_STRING + t[i + 1].start);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "password") == 0) {
      /* We may additionally check if the value is either "true" or "false" */
      printf("\n-Password: %.*s\n", t[i + 1].end - t[i + 1].start,
             JSON_STRING + t[i + 1].start);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "temperature") == 0) {
      /* We may want to do strtol() here to get numeric value */
      printf("\n-Temperature: %.*s\n", t[i + 1].end - t[i + 1].start,
             JSON_STRING + t[i + 1].start);
      i++;
    } else if (jsoneq(JSON_STRING, &t[i], "groups") == 0) {
      int j;
      printf("- Groups:\n");
      if (t[i + 1].type != JSMN_ARRAY) {
        continue; /* We expect groups to be an array of strings */
      }
      for (j = 0; j < t[i + 1].size; j++) {
        jsmntok_t *g = &t[i + j + 2];
        printf("  * %.*s\n", g->end - g->start, JSON_STRING + g->start);
      }
      i += t[i + 1].size + 1;
    } else {
      printf("Unexpected key: %.*s\n", t[i].end - t[i].start,
             JSON_STRING + t[i].start);
    }
  }
  printf("starting Http packet....\n");
http_call(JSON_STRING);
}

Options_after_userauthenticated(int choice)
{
if (choice == 1) {
    int temp;
    int *t = &temp;

    while (1) {
        printf("Please enter the temperature you want to set: ");
        if (scanf("%d", t) != 1) {
            printf("Invalid input. Please enter a numerical value.\n");
            // Clear input buffer
            while (getchar() != '\n');
            continue;  // Prompt again
        } else {
            // Input is numeric, proceed
            break;  // Exit the loop
        }
    }

    snprintf(JSON_STRING, sizeof(JSON_STRING),
             "{\"username\":\"%s\",\"password\":\"%s\",\"temperature\":%d}",
             username, password, temp);
    printf("JSON string: %s\n", JSON_STRING);
    getchar();  // Clear the newline character from input buffer
    jasmin_Parser();
}

else if(choice==2)
{
printf("\nGetting the Temperature Value...");           
}
}

int main()
{
    printf("welcome to smart_thermostat console\n");
    printf("Please eneter valid credentials\n");
    login();
}