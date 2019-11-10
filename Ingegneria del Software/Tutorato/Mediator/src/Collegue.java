
public class Collegue {
	private Mediator m;
	
	Collegue(Mediator m){
		this.m = m;
	}
	
	public void completed(String task) {
		m.taskCompleted(task);
	}
}
