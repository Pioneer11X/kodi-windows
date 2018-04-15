//
//  EventInterface.cpp
//  Kodi
//
//  Created by Sravan Karuturi on 11-04-18.
//  Copyright © 2018 Sravan Karuturi. All rights reserved.
//

#include "EventInterface.hpp"

namespace kodi {
    
    void EventInterface::Construct( )
    {
        
    }
    
    int EventInterface::GetKeyNumber(int key){
        std::multimap<int, int>::iterator itr = keyTranslations.find( key );
        
        return itr->second;
    }
    
    int EventInterface::GetMouseButtonNumber( int key )
    {
        std::multimap<int, int>::iterator itr = mouseButtonTranslations.find( key );
        
        return itr->second;
    }
    
}
