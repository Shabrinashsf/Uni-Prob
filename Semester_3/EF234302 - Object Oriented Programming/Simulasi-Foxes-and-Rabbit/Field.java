import java.util.List;
import java.util.ArrayList;

public class Field {
    private Object[][] field;  
       
      public Field(int row, int col) {  
           field = new Object[row][col];  
      }  
       
      public void place(Object obj, Location location) {  
           field[location.getRow()][location.getCol()] = obj;  
      }  
       
      public void clear(Location location) {  
           field[location.getRow()][location.getCol()] = null;  
      }  
       
      public void clearAll() {  
           for (int i = 0; i < field.length; i++) {  
                for (int j = 0; j < field[i].length; j++) {  
                     field[i][j] = null;  
                }  
           }  
      }
      
      public Object getObjectAt(Location location) {  
           if (location.getRow() >= 0 && location.getRow() < getRow() && location.getCol() >= 0  
             && location.getCol() < getCol()) {  
                return field[location.getRow()][location.getCol()];  
           }  
           return null;  
      }  
       
      public List<Location> getAllFreeNearbyLocs(Location location) {  
           List<Location> availableLocations = new ArrayList<>();  
           List<Location> nearbyLocations = getNearbyLocs(location);  
           for (Location loc : nearbyLocations) {  
                if (getObjectAt(loc) == null) {  
                 availableLocations.add(loc);  
                }  
           }  
           return availableLocations;  
      }  
       
      public Location getFreeNearbyLoc(Location location) {  
           List<Location> freeLocations = getAllFreeNearbyLocs(location);  
           if (freeLocations.size() > 0) {  
                return freeLocations.get(0);  
           }  
           return null;  
      }  
       
      public List<Location> getNearbyLocs(Location location) {  
           List<Location> locations = new ArrayList<>();  
           if (location == null) {  
                return locations;  
           }  
           
           int row = location.getRow();  
           int col = location.getCol();  
           
           if (row > 0) {  
                locations.add(new Location(row - 1, col));  
           }  
           if (row < getRow() - 1) {  
                locations.add(new Location(row + 1, col));  
           }  
           if (col > 0) {  
                locations.add(new Location(row, col - 1));  
           }  
           if (col < getCol() - 1) {  
                locations.add(new Location(row, col + 1));  
           }  
           return locations;  
      }  
       
      public int getRow() {  
           return field.length;  
      }  
       
      public int getCol() {  
           return field[0].length;  
      }
}