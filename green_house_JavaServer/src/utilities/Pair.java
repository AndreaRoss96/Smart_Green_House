package utilities;

public class Pair<K, V> {
	private final K itemKey;
	private final V itemValue;
	
	public Pair(K key, V value) {
		this.itemKey = key;
		this.itemValue = value;
	}
	
	public K getFirst() {
		return this.itemKey;
	}
	
	public V getSecond() {
		return this.itemValue;
	}
}
