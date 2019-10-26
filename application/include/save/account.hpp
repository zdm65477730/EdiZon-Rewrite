/**
 * Copyright (C) 2019 WerWolv
 * 
 * This file is part of EdiZon.
 * 
 * EdiZon is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 * 
 * EdiZon is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with EdiZon.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <edizon.hpp>

#include <string>
#include <vector>

namespace edz::save {

    class Account {
    public:
        Account(userid_t userID, bool exists);

        userid_t getID();
        std::string getIDString();

        std::string getNickname();
        std::vector<u8>& getIcon();

        bool exists();

    private:
        userid_t m_userID;
        bool m_exists;

        std::string m_nickname;
        std::vector<u8> m_icon;
    };

}