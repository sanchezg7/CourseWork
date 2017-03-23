import java.io.BufferedReader;
import java.io.FileReader; //added by Gerardo Sanchez
import java.io.IOException;
import java.util.*;

public class P1 {
	
	/* Define data structures for holding the data here */
	
	Vector <coach> tempCoach = new Vector <coach>(0);  
    Vector <team> tempTeams = new Vector <team>(0);

    public P1() {
        /* initialize the data structures */
    	/*
    	//Test Bench for coaches
    	
    	coach testCoach1 = new coach ("BEGIN01", "1993", "John", "Proba1", "32", "50", "2", "0", "HOU" );
    	coach testCoach2 = new coach ("JONESKC01", "1992", "KC", "Jones", "48", "34", "3", "4", "WAC");
    
    	tempCoach.add(testCoach1);
    	tempCoach.add(testCoach2);
    	
    	
    	//Test bench for teams
    	
    	team testTeam1 = new team ("Begin", "Begin", "fuuls", "N");
    	team testTeam2 = new team ("WA1", "Washington", "Bullets", "N");
    	
    	tempTeams.add(testTeam1);
    	tempTeams.add(testTeam2);
    	
    	*/
    }
    
    public void run() {
        CommandParser parser = new CommandParser();

        System.out.println("The mini-DB of NBA coaches and teams");
        System.out.println("Please enter a command.  Enter 'help' for a list of commands.");
        System.out.println();
        System.out.print("> "); 
        
        Command cmd = null;
        while ((cmd = parser.fetchCommand()) != null) {
            //System.out.println(cmd);
            
            boolean result=false;
            
            if (cmd.getCommand().equals("help")) {
                result = doHelp();

		/* You need to implement all the following commands */
            } else if (cmd.getCommand().equals("add_coach")) { 
            	
	            	//Parameters in order 0: ID, 1: seasonYear, 2:first, 3: last, 4:sWin, 5: sLoss, 6: pWin, 7:, pLoss, 8:team
	            	//add specified coach with the given parameters to the vector
	            	
	            	String parameters[] = cmd.getParameters();
	            	
	            	//input size validation
	            	if(parameters.length == 9){
						//making coach instance with the given parameters in respective order for the constructor
						//appending the new coach on the vector database
						tempCoach.add(new coach(parameters[0], parameters[1], parameters[2], parameters[3],
								parameters[4], parameters[5], parameters[6], parameters[7], parameters[8]));
	            	}
	                      		
	            	else {
	            		System.out.println("Error: add_coach requires 8 parameters");
	            	}
	    } else if (cmd.getCommand().equals("add_team")) { 
	    	
	    		//Parameters in order 0: ID, 1: Location, 2: Name, 3: League(CHAR data type)
	    		String parameters[] = cmd.getParameters();
	    		
	    		if (parameters.length == 4){
	    			//make temporary team instance and add it to the vector database
	    			tempTeams.add(new team(parameters[0], parameters[1], parameters[2], parameters[3]));
	    		}
	    		else {
	    			System.out.println("Error: add_team requires 4 parameters");
	    		}
	    	
	    			
        	
		} else if (cmd.getCommand().equals("print_coaches")) {
			
				//iterate through all coaches and print their respective data members followed by a new line
				//end iteration at the end of the coach vector data structure 
				
		
				for(int i = 0; i < tempCoach.size(); ++i) {
					//print coachID, first, last, seasonW, seasonL, playoffW, playoffL, team
					System.out.println(tempCoach.get(i).getID() + "\t" + tempCoach.get(i).getSeasonYear()
										+ "\t" + tempCoach.get(i).getFirst() + "\t" + tempCoach.get(i).getLast() 
										+ "\t" + tempCoach.get(i).getseasonWin() + "\t"+ tempCoach.get(i).getseasonLoss()
										+ "\t" + tempCoach.get(i).getPlayOffWin() + "\t" + tempCoach.get(i).getPlayOffLoss()
										+ "\t" + tempCoach.get(i).getTeam());	
				}

	   	} else if (cmd.getCommand().equals("print_teams")) { 
	   		
		   		//iterate through all of the teams and print their respective data members
		   		for(int i = 0; i < tempTeams.size(); ++i) {
		   			//print teamID, Location, Name, League
		   			System.out.println(tempTeams.get(i).getID() + "\t" + tempTeams.get(i).getLocation()
		   								+ "\t" + tempTeams.get(i).getName() + "\t" + tempTeams.get(i).getLeague());
		   		}

		} else if (cmd.getCommand().equals("coaches_by_name")) { 
				//retrieve the search criteria
				String parameters[] = cmd.getParameters();
				
				//input validation
				if(parameters.length == 1) {
				 
					//adjust parameter to get rid of "+" and replace it with white space
					parameters[0] = parameters[0].replace('+', ' ');
					
					
					//search through vector to find matches with criteria
					//print the results as they are found
					for(int i=0; i<tempCoach.size(); ++i) {
						if(parameters[0].equals(tempCoach.get(i).getLast())) {
														
							System.out.println(tempCoach.get(i).getID() + "\t" + tempCoach.get(i).getSeasonYear()
									+ "\t " + tempCoach.get(i).getFirst() + "\t" + tempCoach.get(i).getLast() 
									+ "\t" + tempCoach.get(i).getseasonWin() + "\t"+ tempCoach.get(i).getseasonLoss()
									+ "\t" + tempCoach.get(i).getPlayOffWin() + "\t" + tempCoach.get(i).getPlayOffLoss()
									+ "\t" + tempCoach.get(i).getTeam());
									
						}
					}
				}
				else {
					System.out.println("Error: coaches_by_name requires 1 parameter");
				}
			
		} else if (cmd.getCommand().equals("teams_by_city")) {
					String parameters[] = cmd.getParameters();
					
					//input validation
					if(parameters.length == 1) {
						for(int i=0; i<tempTeams.size(); ++i){
							if(parameters[0].equals(tempTeams.get(i).getLocation()))
							{
								System.out.println(tempTeams.get(i).getID() + "\t" + tempTeams.get(i).getLocation()
		   								+ "\t" + tempTeams.get(i).getName() + "\t" + tempTeams.get(i).getLeague());
							}
						}
					}
					else {
						System.out.println("Error: teams_by_city requires 1 parameter");
					}

		} else if (cmd.getCommand().equals("load_coaches")) {
					String parameters[] = cmd.getParameters();
					String temp;
					try{
						BufferedReader fileIn = new BufferedReader(new FileReader(parameters[0]));
						temp = fileIn.readLine();
						//read a line at a time in the file until reaching EOF
						while( (temp = fileIn.readLine())!= null){
							//split file into an array of entries by comma
							String entries[] = temp.split(","); //there will be 9 elements in order for the coach object
							
							//organize respective elements and create a new coach object to place into the database
							tempCoach.add(new coach(entries[0],entries[1],entries[3], entries[4], entries[5],
									entries[6], entries[7], entries[8], entries[9]));
						}
						fileIn.close(); //close the current file
					}
					catch(IOException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
						
					}
		
        } else if (cmd.getCommand().equals("load_teams")) {
        		String parameters[] = cmd.getParameters();
        		String temp;
        		
        		//throws an exception if the program cannot open the specified file
        		try{
        			//open the file
        			BufferedReader fileIn = new BufferedReader(new FileReader(parameters[0]));
        			
        			//read a line one by one until EOF
        			while((temp = fileIn.readLine()) != null){
        				//split file in commas
        				String entries[] = temp.split(","); //will have 4 entries for each team
        				
        				//organize the elements into the vector database
        				tempTeams.add(new team(entries[0], entries[1], entries[2], entries[3]));
        			}
        			fileIn.close(); //close
        		}
        		catch (IOException e){
        			e.printStackTrace();
        		}
		
		} else if (cmd.getCommand().equals("best_coach")) {
					String parameters[] = cmd.getParameters();
					coach bestCoach = null;
					
					//input validation for parameters
					if(parameters.length == 1) {
						
						for(int j=0; j<tempCoach.size(); ++j) {
							if(parameters[0].equals(tempCoach.get(j).getSeasonYear()))
							{
								System.out.println("inital best set");
								bestCoach = tempCoach.get(j); //assign the best coach to the first instance that match the season year
								break; //exit loop once this condition is met
							}
						}
						
						//compare with the rest of the database and update the best coach if needed
						for(int i=0; i<tempCoach.size(); ++i){
							if(parameters[0].equals(tempCoach.get(i).getSeasonYear())){
								if((tempCoach.get(i).netWins()) > bestCoach.netWins()){
									
									bestCoach = tempCoach.get(i); //assign the new best coach
									
								}
							}
								
						}
						System.out.println(bestCoach.getID() + "\t" + bestCoach.getSeasonYear()
											+ "\t " + bestCoach.getFirst() + "\t" + bestCoach.getLast() 
											+ "\t" + bestCoach.getseasonWin() + "\t"+ bestCoach.getseasonLoss()
											+ "\t" + bestCoach.getPlayOffWin() + "\t" + bestCoach.getPlayOffLoss()
											+ "\t" + bestCoach.getTeam());
					}
					else{
						System.out.println("Error: best_coaches requires 1 parameter");
					}
					

		} else if (cmd.getCommand().equals("search_coaches")) {
					String parameters[] = cmd.getParameters(); //load given parameters
					Vector <coach> searchResults = new Vector <coach>(0);
					Vector <coach> orig = new Vector <coach>();
					for(int i = 0; i<tempCoach.size(); ++i){
						orig.add(tempCoach.get(i));
					}
					int iteration = 1;
					
					//input validation to make sure at least one parameter is passed
					if(parameters.length >= 1){
						
						for(int i=0; i<parameters.length; ++i){ //run through all the parameters
							
							//each parameter will be split into a field and value string array
							String fieldAndValue[] = parameters[i].split("="); //element 0 is parameter and 1 is the value
							
							
							
							//use the helper function to return a filtered copy of the coaches vector
							//do this until parameters size is reached in loops
							//filter objects out that do not fit the value for the parameter given 
							//insert the FIELD from index 0 and the VALUE from index 1
							if(iteration == 1){
								//only use the original database the first time
								searchResults = searchFunction( orig, fieldAndValue[0], fieldAndValue[1]); //filter from here but use next parameter
								iteration++;
							}else{
								//every time after that the function used the filtered results and updates it
								
								searchResults = searchFunction(searchResults, fieldAndValue[0], fieldAndValue[1]);
							}
									
							
						}
					if(searchResults.size() == 0){
						System.out.println("search returned no results");
					}
					else{
						for(int i = 0; i < searchResults.size(); ++i) {
							//print coachID, first, last, seasonW, seasonL, playoffW, playoffL, team
							System.out.println(searchResults.get(i).getID() + "\t" + searchResults.get(i).getSeasonYear()
												+ "\t" + searchResults.get(i).getFirst() + "\t" + searchResults.get(i).getLast() 
												+ "\t" + searchResults.get(i).getseasonWin() + "\t"+ searchResults.get(i).getseasonLoss()
												+ "\t" + searchResults.get(i).getPlayOffWin() + "\t" + searchResults.get(i).getPlayOffLoss()
												+ "\t" + searchResults.get(i).getTeam());	
						}
					}
				}
				else{ //no parameters were passed
						System.out.println("Error: search_coaches requires 1 or more parameters");
				}
					
					

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
    
public Vector<coach>  searchFunction (Vector<coach> original, String field, String value){ //filters by one criteria at a time
    	Vector <coach> filtered = new Vector <coach>(); //creates temporary vector to return 
    	//avoids pointer issues
    	
    	//this function will handle one argument at a time and augment it to a temporary vector
    	//this function can be run multiple times to filter out objects that do not belong 
    	
    	for(int i = 0; i<original.size(); ++i){
    		
    		if(field.equals("Coach_ID")){
    			if(value.equals(original.get(i).getID()))
    				filtered.add(original.get(i));
    		} else if(field.equals("season")){
    					if(value.equals(original.get(i).getSeasonYear()))
    						filtered.add(original.get(i));
    		} else if(field.equals("first_name ") || field.equals("firstname")){ //accepts both methods
						if(value.equals(original.get(i).getFirst()))
								filtered.add(original.get(i));
    		} else if(field.equals("last_name") || field.equals("lastname")){
    					if(value.equals(original.get(i).getLast())) {
    							filtered.add(original.get(i));
    					}
    		} else if(field.equals("season_win")){
						if(value.equals(original.get(i).getseasonWin())) {
								filtered.add(original.get(i));
						}
    		} else if(field.equals("season_loss")){
						if(value.equals(original.get(i).getseasonLoss())) {
								filtered.add(original.get(i));
						}
    		} else if(field.equals("playoff_win")){
						if(value.equals(original.get(i).getPlayOffWin())) {
								filtered.add(original.get(i));
						}
    		} else if(field.equals("playoff_loss")){
						if(value.equals(original.get(i).getPlayOffLoss())){
								filtered.add(original.get(i));
						}
    		} else if(field.equals("team")){
						if(value.equals(original.get(i).getTeam())){
								filtered.add(original.get(i));
						}
    		}
    	}
    	
    	return filtered;
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
