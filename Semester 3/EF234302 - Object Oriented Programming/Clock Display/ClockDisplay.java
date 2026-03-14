class ClockDisplay {
    private final NumberDisplay hours;
    private final NumberDisplay minutes;
    private final NumberDisplay seconds;

    public ClockDisplay(int hour, int minute, int second) {
        hours = new NumberDisplay(24);
        minutes = new NumberDisplay(60);
        seconds = new NumberDisplay(60);
        setTime(hour, minute, second);
    }

    public void timeTick() {
        seconds.increment();
        if (seconds.getValue() == 0) {
            minutes.increment();
            if (minutes.getValue() == 0) {
                hours.increment();
            }
        }
    }

    public void setTime(int hour, int minute, int second) {
        hours.setValue(hour);
        minutes.setValue(minute);
        seconds.setValue(second);
    }

    public String getTime() {
        return hours.getDisplayValue() + ":" +
               minutes.getDisplayValue() + ":" +
               seconds.getDisplayValue();
    }
}