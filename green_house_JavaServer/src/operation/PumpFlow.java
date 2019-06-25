package operation;

public enum PumpFlow {
    Pmin("l"), Pmed("m"), Pmax("h"), Zero("z");

    private String value;

    PumpFlow(String value) {
        this.value = value;
    }

    public String getValue() {
        return value;
    }
}
