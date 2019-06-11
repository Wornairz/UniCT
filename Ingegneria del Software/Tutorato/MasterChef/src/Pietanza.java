
public abstract class Pietanza { //Component
	
	public abstract void mostra(String identazione);
	public abstract int calcolaCalorie();
	
	public Pietanza add(Pietanza p) {
		return this;
	}
	public Pietanza remove(Pietanza p) {
		return this;
	}
}
