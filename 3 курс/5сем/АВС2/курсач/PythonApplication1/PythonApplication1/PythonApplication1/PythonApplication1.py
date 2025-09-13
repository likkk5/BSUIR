import tkinter as tk
from datetime import datetime
import json

filename = r"C:\PARKING_JSON\parking_status.json"

def load_parking_status(filename):
    try:
        with open(filename, "r") as file:
            return json.load(file)
    except FileNotFoundError:
        return {}

def update_interface():
    data = load_parking_status(filename)
    for i, (slot, info) in enumerate(data.items()):
        if info["unknwn_obj"]:
            # Set the fill and outline for the parking slot
            canvas.itemconfig(parking_slots[i], fill="yellow", outline="gold")
            
            # Position '?' slightly below the center of the parking slot
            canvas.itemconfig(status_texts[i], text="?", fill="black", font=("Arial", 50, "bold"))
            
            # Position the '?' text slightly below the center of the parking slot
            x1, y1, x2, y2 = canvas.bbox(parking_slots[i])
            center_x = (x1 + x2) // 2
            question_mark_y = (y1 + y2) // 2  # Position it vertically at the center of the parking slot
            canvas.coords(status_texts[i], center_x, question_mark_y)
            
            # Set the error message
            error_labels[i].config(text="Unknown object detected", fg="red")
        elif info["status"] == "free":
            canvas.itemconfig(parking_slots[i], fill="white", outline="green")
            canvas.itemconfig(status_texts[i], text="Free", fill="green", font=("Arial", 12, "italic"))
            
            # Display errors if any
            errors = []
            for error_type, error_value in info.items():
                if "error" in error_type and error_value:
                    errors.append(f"{error_value}")
            error_text = "\n".join(errors) if errors else "No Errors"
            error_labels[i].config(text=error_text, fg="red" if errors else "green")
        else:
            start_time = datetime.fromisoformat(info["start_time"])
            duration = datetime.now() - start_time
            duration_minutes = duration.total_seconds() // 60
            duration_seconds = int(duration.total_seconds() % 60)
            
            # Check if the parked time exceeds 2 hours (120 minutes)
            if duration_minutes >= 120:
                message = f"Parked ({int(duration_minutes)} min {duration_seconds} sec)\nPayment Needed"
                canvas.itemconfig(parking_slots[i], fill="orange", outline="darkorange")
                canvas.itemconfig(status_texts[i], text=message, fill="orange", font=("Arial", 12, "bold"))
            else:
                message = f"Parked ({int(duration_minutes)} min {duration_seconds} sec)"
                canvas.itemconfig(parking_slots[i], fill="red", outline="darkred")
                canvas.itemconfig(status_texts[i], text=message, fill="brown", font=("Arial", 12, "bold"))
            
            # Display errors if any
            errors = []
            for error_type, error_value in info.items():
                if "error" in error_type and error_value:
                    errors.append(f"{error_value}")
            error_text = "\n".join(errors) if errors else "No Errors"
            error_labels[i].config(text=error_text, fg="red" if errors else "green")

    root.after(1000, update_interface)

# Initialize main window
root = tk.Tk()
root.title("Parking Lot Monitoring System")
root.pack_propagate(False)  # Prevent automatic resizing of the window

canvas_width = 800
canvas_height = 400
canvas = tk.Canvas(root, width=canvas_width, height=canvas_height, bg="lightgray")
canvas.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

parking_slots = []
status_texts = []
error_labels = []

slot_width = 150
slot_height = 300
text_offset = 20

parking_data = load_parking_status(filename)
slots = list(parking_data.keys())

# Calculate positions to evenly space slots
total_slots = len(slots)
space_between_slots = (canvas_width - (total_slots * slot_width)) // (total_slots + 1)

# Set larger error frame height
error_frame_height = 250  # Increased from 70 to 120

for i, slot in enumerate(slots):
    x1 = space_between_slots * (i + 1) + slot_width * i
    y1 = (canvas_height - slot_height) // 2
    x2 = x1 + slot_width
    y2 = y1 + slot_height

    # Draw parking slot with realistic styling
    parking_slot = canvas.create_rectangle(
        x1, y1, x2, y2, fill="white", outline="green", width=5
    )
    parking_slots.append(parking_slot)

    # Draw slot number above the slot
    canvas.create_text(
        (x1 + x2) // 2, y1 - text_offset, text=f"{slot}", font=("Arial", 14, "bold"), fill="black"
    )

    # Draw status text below the slot
    status_text = canvas.create_text(
        (x1 + x2) // 2, y2 + text_offset, text="Free", font=("Arial", 12, "italic"), fill="green"
    )
    status_texts.append(status_text)

    # Create error frame for each slot
    error_frame = tk.Frame(root, bg="white", bd=2, relief=tk.SUNKEN)
    error_frame.place(
        x=x1 if i == 0 else x2 - 150,  # Left under Slot 1, Right under Slot 2
        y=y2 + 40,  # Below the canvas
        width=150, 
        height=error_frame_height  # Set the larger error frame height here
    )
    
    # Add "Error Details" title in the frame
    title_label = tk.Label(
        error_frame, text="Error Details", font=("Arial", 10, "bold"), bg="white", anchor="n", fg="black"
    )
    title_label.pack(fill=tk.X, pady=2)

    # Add error label with wraplength to handle long messages
    error_label = tk.Label(
        error_frame, 
        text=f"{slot}: No Errors", 
        font=("Arial", 10), 
        bg="white", 
        anchor="w", 
        justify="left", 
        wraplength=140  # Set wraplength to allow text to wrap
    )
    error_label.pack(fill=tk.BOTH, padx=5, pady=2)
    error_labels.append(error_label)

# Update window height based on the number of error frames and larger frame height
new_window_height = canvas_height + len(slots) * error_frame_height  # Adjusted for larger frame height
root.geometry(f"{canvas_width}x{new_window_height}")  # Set the new window height

update_interface()
root.mainloop()
