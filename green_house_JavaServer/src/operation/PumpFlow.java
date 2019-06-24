package operation;

public enum PumpFlow {
    Pmin("l"), Pmed("m"), Pmax("h"), Off("z");

    private String value;

    PumpFlow(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }
}
