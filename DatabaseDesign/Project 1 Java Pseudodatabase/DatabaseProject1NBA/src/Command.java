
/**
 * Data container for an individual Command
 * 
 * @author dbettis
 */
public class Command {

	public Command(String command, String[] parameters) {
		super();
		this.command = command;
		this.parameters = parameters;
	}
	
	public String getCommand() {
		return command;
	}
	
	public String[] getParameters() {
		return parameters;
	}

	public String toString() {
		StringBuffer sb = new StringBuffer();
		sb.append("Command: " + command + "\n");
		for (int i = 0; i < parameters.length; i++) {
			sb.append("parameters[");
			sb.append(i);
			sb.append("] = ");
			sb.append(parameters[i]);
			sb.append("\n");
		}
		return sb.toString();
	}
	
	private String command;
	private String[] parameters;
}
