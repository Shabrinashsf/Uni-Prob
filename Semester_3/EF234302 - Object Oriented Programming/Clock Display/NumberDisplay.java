class NumberDisplay {
    private final int limit;
    private int value;

    public NumberDisplay(int limit) {
        this.limit = limit;
        this.value = 0;
    }

    public void increment() {
        value = (value + 1) % limit;
    }

    public void setValue(int newValue) {
        if (newValue >= 0 && newValue < limit) {
            value = newValue;
        }
    }

    public int getValue() {
        return value;
    }

    public String getDisplayValue() {
        return String.format("%02d", value);
    }
}