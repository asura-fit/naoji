Naoji: Nao Java Interface.

  Copyright (C) 2009 ASURA-FIT

  This program is free software; you can redistribute it and/or modify it
  under the terms of the GNU General Public License as published by the Free
  Software Foundation; either version 2 of the License, or (at your option)
  any later version.

  This program is distributed in the hope that it will be useful, but WITHOUT
  ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for
  more details.

  You should have received a copy of the GNU General Public License along
  with this program; if not, write to the Free Software Foundation, Inc., 59
  Temple Place, Suite 330, Boston, MA 02111-1307 USA

naoji is a Java Interface for Aldebaran Robotics's software platform Naoqi.
"Nao" and "Naoqi" are developed by Aldebaran Robotics.
"Naoji" is developed by ASURA-FIT 2009.

**LICENSE
Naoji is provided under GPL with "CLASSPATH" EXCEPTION. See LICENSE.txt

**INSTALL OpenJDK**
You can use OpenJDK on Nao with following procedure.
1. Setup Bitbake and OpenEmbedded on your host computer.
http://www.openembedded.org/

2. Get latest Jalimo packages from Jalimo SVN repository.
https://wiki.evolvis.org/jalimo/index.php/Jalimo

3. Edit bitbake configuration.
distro and machine definitions are provided by Aldebaran Robotics.
Using same library version with Nao are recommended.

4. Run bitbake openjdk-6-6b14.
However, Currently some patches are required to build openjdk for i486 target.
see http://lists.evolvis.org/pipermail/jalimo-info/2009-March/000279.html

5. Install openjdk-6-jre-VERSION.ipk to your Nao.
Run opkg command on Nao.
  opkg install openjdk-6-jre-VERSION.ipk DEPENDED_LIBRARIES.ipk

ASURA-FIT 2009:
Manufacturing Center RoboCup project team,
Department of Computer Science and Engineering Ishii lab.,
Department of Information and Systems Engineering Yamaguchi lab.,
Fukuoka Institute of Technology.
