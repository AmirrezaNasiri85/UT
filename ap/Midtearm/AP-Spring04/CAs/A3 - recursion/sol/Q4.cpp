#include <iostream>
#include <string>
#include <vector>

using namespace std;

const int MAX_N = 100;
const int MAX_M = 100;
const int START = 0;
const int NEXT = 1;
const int NUMBER_OF_EMPIRES = 10;
const char ZERO = '0';
const bool SEEN = true;
const bool NOT_SEEN = false;
const bool IS_LAND = true;
const bool IS_NOT_LAND = false;
const bool IN_RANGE = true;
const bool NOT_IN_RANGE = false;
const bool CAN_TRAVERSE = true;
const bool CANT_TRAVERSE = false;
const bool IS_MOUNTAIN = true;
const bool IS_NOT_MOUNTAIN = false;
const bool IS_THE_SAME = true;
const bool IS_NOT_THE_SAME = false;
const bool IN_WATER = true;
const bool NOT_IN_WATER = false;
const int NO_LANDS = 0;
const int FIRST_EMPIRE = 0;
const int LAST_EMPIRE = 9;
const int OUT_OF_RANGE_NEGATIVE = -1;
const int AN_EXTRA_LAND_FOR_EMPIRE = 1;
const bool IS_NOT_PORT = false;
const bool IS_NOT_OCEAN = false;

namespace movementdirection {
const int UP = 1;
const int DOWN = -1;
const int LEFT = -1;
const int RIGHT = 1;
}; // namespace movementdirection

namespace landtype {
const char OCEAN = '~';
const char MOUNTAIN = '#';
const char PORT = '%';
}; // namespace landtype

struct WorldMap {
    int n, m;
    bool flags[MAX_N][MAX_M];
    char lands[MAX_N][MAX_M];
    int largest_empires_states[NUMBER_OF_EMPIRES];
};

struct Location {
    int i;
    int j;
    char starting_empire;
    bool can_traverse_water;
    bool in_water;
};

void readLandsInfo(WorldMap& world_map) {
    cin >> world_map.n >> world_map.m;
    string input_line;
    for (int i = START; i < world_map.n; i += NEXT) {
        cin >> input_line;
        for (int j = START; j < world_map.m; j += NEXT) {
            world_map.lands[i][j] = input_line[j];
        }
    }
}

void resetAllFlags(bool (&flags)[MAX_N][MAX_M]) {
    for (int i = START; i < MAX_N; i += NEXT) {
        for (int j = START; i < MAX_M; i += NEXT) {
            flags[i][j] = NOT_SEEN;
        }
    }
}

void resetEmpireStateSize(WorldMap& world_map) {
    for (int i = FIRST_EMPIRE; i <= LAST_EMPIRE; i += NEXT) {
        world_map.largest_empires_states[i] = NO_LANDS;
    }
}

int landToEmpireName(char land) {
    return land - ZERO;
}

bool isLand(int land) {
    return ((land <= LAST_EMPIRE && land >= FIRST_EMPIRE) ? IS_LAND : IS_NOT_LAND);
}

void resetNotLand(WorldMap& world_map) {
    for (int i = START; i < MAX_N; i += NEXT) {
        for (int j = START; j < MAX_M; j += NEXT) {
            if (isLand(landToEmpireName(world_map.lands[i][j])) == IS_NOT_LAND) {
                world_map.flags[i][j] = NOT_SEEN;
            }
        }
    }
}

bool inRange(Location location, WorldMap world_map) {
    if (location.i >= world_map.n || OUT_OF_RANGE_NEGATIVE >= location.i) return NOT_IN_RANGE;
    if (location.j >= world_map.m || OUT_OF_RANGE_NEGATIVE >= location.j) return NOT_IN_RANGE;
    return IN_RANGE;
}

bool isMountain(Location location, WorldMap world_map) {
    if (world_map.lands[location.i][location.j] == landtype::MOUNTAIN) {
        return IS_MOUNTAIN;
    }
    return IS_NOT_MOUNTAIN;
}

bool hasBeenSeenBefore(Location location, WorldMap world_map) {
    if (world_map.flags[location.i][location.j] == SEEN) {
        return SEEN;
    }
    return NOT_SEEN;
}

bool isTheSameEmpire(Location& location, WorldMap world_map) {
    if (world_map.lands[location.i][location.j] == location.starting_empire && location.in_water == NOT_IN_WATER) {
        location.can_traverse_water = CANT_TRAVERSE;
        return IS_THE_SAME;
    }
    return IS_NOT_THE_SAME;
}

bool checkTravelToPort(Location& location, WorldMap world_map) {
    if (world_map.lands[location.i][location.j] != landtype::PORT) {
        return IS_NOT_PORT;
    }
    location.can_traverse_water = CAN_TRAVERSE;
    location.in_water = NOT_IN_WATER;
    return CAN_TRAVERSE;
}

bool checkTravelToOcean(Location& location, WorldMap world_map) {
    if (world_map.lands[location.i][location.j] != landtype::OCEAN) {
        return IS_NOT_OCEAN;
    }
    if (location.can_traverse_water == CAN_TRAVERSE) {
        location.in_water = IN_WATER;
        return CAN_TRAVERSE;
    }
    return CANT_TRAVERSE;
}

bool checkCanMoveToLand(WorldMap& world_map, Location& location) {
    if (inRange(location, world_map) == NOT_IN_RANGE) return CANT_TRAVERSE;
    if (hasBeenSeenBefore(location, world_map) == SEEN) return CANT_TRAVERSE;
    if (isMountain(location, world_map) == IS_MOUNTAIN) return CANT_TRAVERSE;
    if (isTheSameEmpire(location, world_map) == IS_THE_SAME) return CAN_TRAVERSE;
    if (checkTravelToPort(location, world_map) == CAN_TRAVERSE) return CAN_TRAVERSE;
    if (checkTravelToOcean(location, world_map) == CAN_TRAVERSE) return CAN_TRAVERSE;
    return CANT_TRAVERSE;
}

bool isALandOfEmpire(Location location, WorldMap world_map) {
    if (world_map.lands[location.i][location.j] == location.starting_empire) {
        return IS_LAND;
    }
    return IS_NOT_LAND;
}

vector<Location> generateAdjacentLocations(Location location) {
    vector<Location> adjacent_locations;
    Location adjacent_location_up = location;
    adjacent_location_up.i += movementdirection::UP;
    Location adjacent_location_down = location;
    adjacent_location_down.i += movementdirection::DOWN;
    Location adjacent_location_left = location;
    adjacent_location_left.j += movementdirection::LEFT;
    Location adjacent_location_right = location;
    adjacent_location_right.j += movementdirection::RIGHT;
    adjacent_locations.push_back(adjacent_location_up);
    adjacent_locations.push_back(adjacent_location_down);
    adjacent_locations.push_back(adjacent_location_left);
    adjacent_locations.push_back(adjacent_location_right);
    return adjacent_locations;
}

int findLargestEmpire(WorldMap& world_map, Location& location) {
    vector<Location> adjacent_locations;
    int largest_empire_size = NO_LANDS;
    if (isALandOfEmpire(location, world_map)) largest_empire_size += AN_EXTRA_LAND_FOR_EMPIRE;
    world_map.flags[location.i][location.j] = SEEN;
    adjacent_locations = generateAdjacentLocations(location);
    for (auto next_location : adjacent_locations) {
        if (checkCanMoveToLand(world_map, next_location)) {
            largest_empire_size += findLargestEmpire(world_map, next_location);
        }
    }
    return largest_empire_size;
}

void solve(WorldMap& world_map) {
    for (int i = START; i < world_map.n; i += NEXT) {
        for (int j = START; j < world_map.m; j += NEXT) {
            int current_empire_name = landToEmpireName(world_map.lands[i][j]);
            if (isLand(current_empire_name) && world_map.flags[i][j] == NOT_SEEN) {
                Location location{i, j, world_map.lands[i][j], CANT_TRAVERSE, NOT_IN_WATER};
                int new_state_size = findLargestEmpire(world_map, location);
                int previous_max_state_size = world_map.largest_empires_states[current_empire_name];
                world_map.largest_empires_states[current_empire_name] = max(previous_max_state_size, new_state_size);
                resetNotLand(world_map);
            }
        }
    }
}

void printEmpiresLargestStatesSize(WorldMap world_map) {
    for (int i = FIRST_EMPIRE; i <= LAST_EMPIRE; i += NEXT) {
        cout << world_map.largest_empires_states[i] << endl;
    }
}

void cleanUpWorldMap(WorldMap& world_map) {
    resetEmpireStateSize(world_map);
    resetAllFlags(world_map.flags);
}

void run() {
    WorldMap world_map;
    cleanUpWorldMap(world_map);
    readLandsInfo(world_map);
    solve(world_map);
    printEmpiresLargestStatesSize(world_map);
}

int main() {
    run();
    return 0;
}