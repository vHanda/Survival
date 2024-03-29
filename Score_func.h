/*
 * Survival
 *
 * Copyright (C) 2009-2011 Vishesh Handa <me@vhanda.in>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef SCORE_FUNC_H_INCLUDED
#define SCORE_FUNC_H_INCLUDED

#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "tinyxml/tinyxml.h"

class hScore {
public :
    std::string name;
    int killed;
    int time;

    bool operator<(const hScore & rhs) const {
        return time < rhs.time;
    }
};

inline std::string toString(int i)
{
    std::stringstream ss;
    ss << i;
    return ss.str();
}

inline void load_score(std::vector<hScore> & list)
{
    TiXmlDocument doc("data/score");
    doc.LoadFile();

    TiXmlElement * pRoot = doc.FirstChildElement();
    TiXmlElement * pScore = pRoot->FirstChildElement();
    while(pScore != NULL)
    {
        hScore sc;
        sc.name = pScore->FirstChildElement("name")->GetText();
        sc.killed = atoi(pScore->FirstChildElement("killed")->GetText());
        sc.time = atoi(pScore->FirstChildElement("time")->GetText());

        list.push_back(sc);
        pScore = pScore->NextSiblingElement();
    }
}

inline void save_score(std::vector<hScore> & list)
{
    TiXmlDocument doc;

    TiXmlElement * pRoot = new TiXmlElement("score");
    doc.LinkEndChild(pRoot);

    for(unsigned int i=0; i<list.size(); i++)
    {
        TiXmlElement * pHighScore = new TiXmlElement("highscore");
        TiXmlElement * pName = new TiXmlElement("name");
        TiXmlElement * pKilled = new TiXmlElement("killed");
        TiXmlElement * pTime = new TiXmlElement("time");

        hScore sc = list[i];

        TiXmlText * name = new TiXmlText(sc.name.c_str());
        TiXmlText * killed = new TiXmlText( toString(sc.killed).c_str() );
        TiXmlText * time = new TiXmlText( toString(sc.time).c_str() );

        pName->LinkEndChild(name);
        pKilled->LinkEndChild(killed);
        pTime->LinkEndChild(time);

        pHighScore->LinkEndChild(pName);
        pHighScore->LinkEndChild(pKilled);
        pHighScore->LinkEndChild(pTime);

        pRoot->LinkEndChild(pHighScore);
    }
    doc.SaveFile("data/score");
}

#endif // SCORE_FUNC_H_INCLUDED
