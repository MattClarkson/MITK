/*=========================================================================

Program:   Medical Imaging & Interaction Toolkit
Module:    $RCSfile$
Language:  C++
Date:      $Date$
Version:   $Revision$

Copyright (c) German Cancer Research Center, Division of Medical and
Biological Informatics. All rights reserved.
See MITKCopyright.txt or http://www.mitk.org/copyright.html for details.

This software is distributed WITHOUT ANY WARRANTY; without even
the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE.  See the above copyright notices for more information.

=========================================================================*/

#include "mitkDataStorage.h"

#include "mitkDataTreeNode.h"
#include "mitkProperties.h"
#include "mitkNodePredicateBase.h"

mitk::DataStorage::DataStorage() 
: itk::Object(), m_ManageCompleteTree(true) // true by default until all Reliver functionalities use the datastorage properly
{
  m_DataTree = NULL;
}

mitk::DataStorage::~DataStorage()
{
  m_DataTree = NULL;
}

void mitk::DataStorage::Initialize(mitk::DataTree* tree)
{
  if (tree == NULL)
    throw 1;  // insert exception handling here 
  m_DataTree = tree;
}

inline bool mitk::DataStorage::IsInitialized()
{
  return m_DataTree.IsNotNull();
}

void mitk::DataStorage::Add(mitk::DataTreeNode* node, const mitk::DataStorage::SetOfObjects* parents)
{
  if (!IsInitialized())
    throw 1;  // insert exception handling here
  /* Check, if node is already in the DataTree */
  if (m_DataTree->Contains(node))
    throw 2;
  /* save node in tree */
  mitk::DataTreePreOrderIterator it(m_DataTree);
  node->SetProperty("IsDataStoreManaged", new mitk::BoolProperty(true));
  it.Add(node);
  /* save node and parentlist in relations map */
  m_CreatedByRelations.insert(make_pair(node, parents)); 

}

void mitk::DataStorage::Update(mitk::DataTreeNode* node)
{
}

mitk::DataStorage::SetOfObjects::ConstPointer mitk::DataStorage::GetSubset(const NodePredicateBase& condition)
{
  if (!IsInitialized())
    throw 1;  // insert exception handling here

  /* Fill resultset with objects that fullfill the condition */
  mitk::DataTreePreOrderIterator it(m_DataTree);
  mitk::DataStorage::SetOfObjects::Pointer resultset = mitk::DataStorage::SetOfObjects::New();
  unsigned int index = 0;
  if (m_ManageCompleteTree == true)
    for (it.GoToBegin(); !it.IsAtEnd(); it++)
    {
      mitk::DataTreeNode* node = it.Get();
      if (node == NULL)
        continue;
      if (condition.CheckNode(node) == true)  // check all elements in the datatree
        resultset->InsertElement(index++, node);
    } 
  else
    for (it.GoToBegin(); !it.IsAtEnd(); it++)
    {
      mitk::DataTreeNode* node = it.Get();
      if (node == NULL)
        continue;
      if ((node->IsOn("IsDataStoreManaged",NULL, false) == true) && (condition.CheckNode(node) == true))  // check if node is managed by the datastorage object
        resultset->InsertElement(index++, node);
    } 
  return SetOfObjects::ConstPointer( resultset );
}

mitk::DataStorage::SetOfObjects::ConstPointer mitk::DataStorage::GetAll()
{
  mitk::DataTreePreOrderIterator it(m_DataTree);
  mitk::DataStorage::SetOfObjects::Pointer resultset = mitk::DataStorage::SetOfObjects::New();
  /* Fill resultset with all objects that are managed by the DataStorage object */
  unsigned int index = 0;
  if (m_ManageCompleteTree == true)
    for (it.GoToBegin(); !it.IsAtEnd(); it++)
    {
      mitk::DataTreeNode* node = it.Get();
      if (node == NULL) 
        continue;
      resultset->InsertElement(index++, node);
    }  
  else
    for (it.GoToBegin(); !it.IsAtEnd(); it++)
    {
      mitk::DataTreeNode* node = it.Get();
      if (node == NULL) 
        continue;
      if (node->IsOn("IsDataStoreManaged",NULL, false) == true)  // check if node is managed by the datastorage object
        resultset->InsertElement(index++, node);
    }  
  return SetOfObjects::ConstPointer( resultset );
}
