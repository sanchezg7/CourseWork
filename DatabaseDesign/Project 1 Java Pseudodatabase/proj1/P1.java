import java.util.*;

public class P1 {
	
	/* Define data structures for holding the data here */
	
	Vector <coach> tempCoach = new Vector <coach>(0);  
    Vector <team> tempTeams = new Vector <team>(0);

    public P1() {
        /* initialize the data structures */
    	
    }
    
    public void run() {
        CommandParser parser = new CommandParser();

        System.out.println("The mini-DB of NBA coaches and teams");
        System.out.println("Please enter a command.  Enter 'help' for a list of commands.");
        System.out.println();
        System.out.print("> "); 
        
        Command cmd = null;
        while ((cmd = parser.fetchCommand()) != null) {
            System.out.println(cmd);
            
            boolean result=false;
            
            if (cmd.getCommand().equals("help")) {
                result = doHelp();

		/* You need to implement all the following commands */
            } else if (cmd.getCommand().equals("add_coach")) {
            
	    } else if (cmd.getCommand().equals("add_team")) {
        	
		} else if (cmd.getCommand().equals("print_coaches")) {
			
					//iterate through all coaches and print their respective data members followed by a new line
					//end iteration at the end of the coach vector data structure 
			
					for(int i = 0; i < tempCoach.size(); ++i)
					{
						//print coachID, first, last, seasonW, seasonL, playoffW, playoffL, team
						// categories separated by tabs
						System.out.println("Temp coach printing out here: \t " + tempCoach.get(i).getID() + "\t");	
					}

	   	} else if (cmd.getCommand().equals("print_teams")) {

		} else if (cmd.getCommand().equals("coaches_by_name")) {

		} else if (cmd.getCommand().equals("teams_by_city")) {

		} else if (cmd.getCommand().equals("load_coaches")) {

        } else if (cmd.getCommand().equals("load_teams")) {
		
		} else if (cmd.getCommand().equals("best_coach")) {

		} else if (cmd.getCommand().equals("search_coaches")) {

		} else if (cmd.getCommand().equals("exit")) {
			System.out.println("Leaving the database, goodbye!");
			break;
		} else if (cmd.getCommand().equals("")) {
		} else {
			System.out.println("Invalid Command, try again!");
           	} 
            
	    if (result) {
                // ...
            }

            System.out.print("> "); 
        }        
    }
    
    private boolean doHelp() {
        System.out.println("add_coach ID SEASON FIRST_NAME LAST_NAME SEASON_WIN "); 
		System.out.println("	SEASON_LOSS PLAYOFF_WIN PLAYOFF_LOSS TEAM - add new coach data");
        System.out.println("add_team ID LOCATION NAME LEAGUE - add a new team");
        System.out.println("print_coaches - print a listing of all coaches");
        System.out.println("print_teams - print a listing of all teams");
        System.out.println("coaches_by_name NAME - list info of coaches with the specified name");
        System.out.println("teams_by_city CITY - list the teams in the specified city");
	    System.out.println("load_coach FILENAME - bulk load of coach info from a file");
        System.out.println("load_team FILENAME - bulk load of team info from a file");
        System.out.println("best_coach SEASON - print the name of the coach with the most netwins in a specified season");
        System.out.println("search_coaches field=VALUE - print the name of the coach satisfying the specified conditions");
		System.out.println("exit - quit the program");        
        return true;
    }
    
    /**
     * @param args
     */
    public static void main(String[] args) {
        new P1().run();
    }
    
    

}
