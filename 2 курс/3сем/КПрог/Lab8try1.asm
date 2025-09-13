.model small
.stack 100h

.data
    device_present db 0       ; Flag indicating device presence
    notification_msg db 'Device detected! Press Esc to reject.', 0
    reject_msg db 'Device rejected', 0

_start:
    ; Initialization code
    jmp monitor_events

monitor_events:
    ; Check for the presence of the device
    ; (Your code for checking the device presence)

    ; Example: Let's assume you have a device on port 0x60
    ; and you want to check if it is connected.

    mov dx, 0x60   ; I/O port for the device
    in al, dx      ; Read the value from the port into AL

    ; Check if the value matches the expected value of your device
    cmp al, expected_value
    je device_detected

    ; If the value doesn't match the expected one, the device is not present
    jmp device_not_present

device_detected:
    ; Code to set the device_present flag
    mov byte [device_present], 1
    jmp further_actions

device_not_present:
    ; Code to handle the case when the device is not detected
    jmp further_actions

further_actions:
    ; Display notification on the screen
    mov ah, 09h  ; Print string function
    lea dx, [notification_msg]
    int 21h

    ; Play a sound using the PC Speaker
    mov ah, 86h  ; Interrupt for the PC Speaker
    int 15h

    ; Wait for key presses
    wait_for_key:
        mov ah, 01h  ; Check for a key press
        int 16h
        jz wait_for_key  ; Repeat monitoring until a key is pressed

        ; If a key is pressed, check if it is the rejection key (Esc)
        cmp ah, 01h
        je reject_device

    ; Other key handling can be added as needed

    jmp monitor_events

reject_device:
    ; Display rejection message
    mov ah, 09h
    lea dx, [reject_msg]
    int 21h

    ; Additional actions upon device rejection
    ; (Your code for rejecting the device)

    ; Terminate the program
    int 20h
