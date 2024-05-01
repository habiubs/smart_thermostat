#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Function to set the HTTP status line
void http_set_status(char *status_line, const char *status) {
    sprintf(status_line, "HTTP/1.1 %s\r\n", status);
}

// Function to set the HTTP headers
void http_set_header(char *headers, const char *header_name, const char *header_value) {
    strcat(headers, header_name);
    strcat(headers, ": ");
    strcat(headers, header_value);
    strcat(headers, "\r\n");
}

// Function to set the HTTP body
void http_set_body(char *body, const char *json_string) {
    strcat(body, json_string);
}

// Modified http_call function to accept JSON_STRING as an argument
int http_call(const char *JSON_STRING) {
    char status_line[128];
    char headers[512];
    char body[1024];

    // Clear buffers
    memset(status_line, 0, sizeof(status_line));
    memset(headers, 0, sizeof(headers));
    memset(body, 0, sizeof(body));

    // Set HTTP status line
    http_set_status(status_line, "200 OK");

    // Set HTTP headers
    http_set_header(headers, "Content-Type", "application/json");
    http_set_header(headers, "Content-Length", "0"); // Replace 0 with the actual length of the body

    // Set HTTP body
    http_set_body(body, JSON_STRING);

    // Print the complete HTTP request
    printf("%s", status_line);
    printf("%s", headers);
    printf("\r\n");
    printf("%s", body);

    return 0;
}
