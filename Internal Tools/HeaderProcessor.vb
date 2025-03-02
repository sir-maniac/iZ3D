''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''''
'' SVN FILE: $Id:$ */
'
'
' $Author:$
' $Copyright$
' $Revision:$
' $Date:$
' $LastChangedBy:$
' $LastChangedDate:$
' $License$
' $URL:$

Imports System
Imports EnvDTE
Imports EnvDTE80
Imports System.Diagnostics
Imports System.IO
Imports System.Collections.Generic


Public Module Module1

    Function GetOutputWindowPane(ByVal Name As String, Optional ByVal show As Boolean = True) As OutputWindowPane
        Dim window As Window
        Dim outputWindow As OutputWindow
        Dim outputWindowPane As OutputWindowPane

        window = DTE.Windows.Item(EnvDTE.Constants.vsWindowKindOutput)
        If show Then window.Visible = True
        outputWindow = window.Object
        Try
            outputWindowPane = outputWindow.OutputWindowPanes.Item(Name)
        Catch e As System.Exception
            outputWindowPane = outputWindow.OutputWindowPanes.Add(Name)
        End Try
        outputWindowPane.Activate()
        Return outputWindowPane
    End Function
    Function ListSubItems(ByRef fsInfo As FileSystemInfo, ByRef target As Object, ByVal level As Integer) As Boolean
        Try
            ' Get item
            Dim fatr As FileAttributes = fsInfo.Attributes And FileAttributes.Directory
            ' if item is directory, process subitems
            If (fatr = FileAttributes.Directory) Then
                Dim dInfo As DirectoryInfo = New DirectoryInfo(fsInfo.FullName)
                ' if directory is ".svn", "lib" then pass throuth
                If dInfo.Name = ".svn" Or dInfo.Name = "lib" Then
                    Return True
                End If
                ' get subitems current directory
                Dim bufInfos As FileSystemInfo() = dInfo.GetFileSystemInfos()

                ' recursive process of subitems
                For Each bufInfo As FileSystemInfo In bufInfos
                    ListSubItems(bufInfo, target, level + 1)
                Next
            Else
                ' if file is not *.cpp, *.h, *.h then pass through
                If (fsInfo.Extension <> ".cpp" And fsInfo.Extension <> ".h" And fsInfo.Extension <> ".rc") Then
                    Return True
                End If
                ' Open file for editing
                'DTE.ItemOperations.OpenFile(fsInfo.FullName)
                ' Get this file as document to edit
                'Dim document As Document = DTE.ActiveDocument

                ' Diagnostic information
                target.OutputString(fsInfo.FullName + "processed")
                target.OutputString(Microsoft.VisualBasic.Constants.vbCrLf)
            End If
        Catch e As Exception
            target.OutputString(e.StackTrace)
        End Try
    End Function
    Sub AddHeaderToAllFiles()
        '' Take the solution
        Dim sol As Solution
        sol = DTE.Solution
        '' file info of solution
        Dim fInfo As FileInfo
        fInfo = New FileInfo(sol.FullName)
        '' directory info of solution
        Dim dInfo As DirectoryInfo = New DirectoryInfo(fInfo.DirectoryName)
        '' all subdirectories and files inside directory
        Dim fsInfos As FileSystemInfo() = dInfo.GetFileSystemInfos()
        Dim fsInfo As FileSystemInfo
        '' window to print information
        Dim target As Object = GetOutputWindow()

        '' for each sub element, process
        For Each fsInfo In fsInfos
            ListSubItems(fsInfo, target, 0)
        Next
    End Sub
    Function GetOutputWindow() As Object
        Dim window As Window = DTE.Windows.Item(Constants.vsWindowKindCommandWindow)
        Dim target As Object
        If (DTE.ActiveWindow Is window) Then
            target = window.Object
        Else
            target = GetOutputWindowPane("List Project")
            target.Clear()
        End If
        Return target
    End Function

    Function ProcessFile(ByRef fsInfo As FileSystemInfo)
        Dim streamReader As StreamReader = New StreamReader(fsInfo.FullName)
        Dim firstLine = streamReader.ReadLine()
        ' if file already has a header
        If firstLine.Contains("/* IZ3D_FILE:") Then
            streamReader.Close()
            RemoveHeaderFromFile(fsInfo)
        Else
            AddHeaderToFile(fsInfo)
        End If
    End Function

    Function ReadFile(ByRef fsInfo As FileSystemInfo) As List(Of String)
        Dim streamReader As StreamReader = New StreamReader(fsInfo.FullName)
        Dim stringList As New List(Of String)
        ' read whole file
        While Not streamReader.EndOfStream
            stringList.Add(streamReader.ReadLine())
        End While
        streamReader.Close()
    End Function

    Function RemoveHeaderFromStrings(ByRef stringList As List(Of String))
        ' remove first string
        stringList.RemoveAt(0)
        ' remove header
        While stringList.Item(0)(0) = "*"
            stringList.RemoveAt(0)
        End While
    End Function

    Function AddHeaderToStrings(ByRef stringList As List(Of String))
        Dim headerStrings As List(Of String) = ReadFile(New FileInfo("header.txt"))
        stringList.InsertRange(0, headerStrings)
    End Function

    Function WriteFile(ByRef stringList As List(Of String), ByRef fsInfo As FileSystemInfo)
        Dim writer As StreamWriter = New StreamWriter(fsInfo.FullName, False)
        For Each bufString As String In stringList
            writer.WriteLine(bufString)
        Next
        writer.Close()
    End Function

    Function RemoveHeaderFromFile(ByRef fsInfo As FileSystemInfo)
        Dim stringList As List(Of String) = ReadFile(fsInfo)
        RemoveHeaderFromStrings(stringList)
        AddHeaderToStrings(stringList)
        WriteFile(stringList, fsInfo)
    End Function

    Function AddHeaderToFile(ByRef fsInfo As FileSystemInfo)
        Dim stringList As List(Of String) = ReadFile(fsInfo)
        AddHeaderToStrings(stringList)
        WriteFile(stringList, fsInfo)
    End Function
End Module