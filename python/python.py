from ics import Calendar, Event
from datetime import datetime, timedelta
import random

# Create a new calendar
c = Calendar()

# Starting date for events
start_date = datetime(2024, 11, 10, 0, 0, 0)

# Generate 1500 random events
for i in range(1500):
    event = Event()
    event.name = f"Random Event {i+1}"
    
    # Random start time offset between 0 and 500 days from start_date
    random_days_offset = random.randint(0, 300)
    random_start_time = start_date + timedelta(days=random_days_offset, minutes=random.randint(0, 24*60))
    
    # Random event duration between 30 minutes and 14 hours
    duration_minutes = random.randint(30, 14 * 60)
    event.begin = random_start_time
    event.duration = timedelta(minutes=duration_minutes)
    
    c.events.add(event)

# Save the generated calendar to a file
with open('large_random_events.ics', 'w') as ics_file:
    ics_file.writelines(c)

print("ICS file with 1500 random events created as 'large_random_events.ics'")
